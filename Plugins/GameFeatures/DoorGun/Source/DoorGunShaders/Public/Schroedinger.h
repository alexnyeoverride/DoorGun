#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformMisc.h"

struct DOORGUNSHADERS_API FSchroedingerDispatchParams
{
	// TODO
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