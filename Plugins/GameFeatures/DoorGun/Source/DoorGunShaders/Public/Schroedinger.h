#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "Schroedinger.generated.h"

struct DOORGUNSHADERS_API FSchroedingerDispatchParams
{
};

class DOORGUNSHADERS_API FSchroedingerInterface
{
public:
	static void DispatchRenderThread(
		FRHICommandListImmediate& RHICmdList,
		FSchroedingerDispatchParams Params,
		TFunction<void(int OutputValue)> AsyncCallback
	);

	static void DispatchGameThread(
		FSchroedingerDispatchParams Params,
		TFunction<void(int OutputValue)> AsyncCallback
	)
	{
		ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
			[Params, AsyncCallback](FRHICommandListImmediate& RHICmdList)
			{
				DispatchRenderThread(RHICmdList, Params, AsyncCallback);					
			}
		);
	}

	static void Dispatch(
		FSchroedingerDispatchParams Params,
		TFunction<void(int OutputValue)> AsyncCallback
	)
	{
		if (IsInRenderingThread())
		{
			DispatchRenderThread(GetImmediateCommandList_ForRenderCommand(), Params, AsyncCallback);
		}
		else
		{
			DispatchGameThread(Params, AsyncCallback);
		}
	}
};


UCLASS()
class DOORGUNSHADERS_API USchroedingerLibrary_AsyncExecution : public UBlueprintAsyncActionBase
{
		GENERATED_BODY()
 
public:
	virtual void Activate() override {
		FSchroedingerDispatchParams Params;
		FSchroedingerInterface::Dispatch(Params, [this](int OutputVal) {});
	}
	
	static USchroedingerLibrary_AsyncExecution* ExecuteBaseComputeShader(UObject* WorldContextObject)
	{
		USchroedingerLibrary_AsyncExecution* Action = NewObject<USchroedingerLibrary_AsyncExecution>();
		Action->RegisterWithGameInstance(WorldContextObject);
		return Action;
	}
};