#pragma once

#include "GenericPlatform/GenericPlatformMisc.h"

class DOORGUNSHADERS_API FSchroedingerInterface
{
public:
	static void Dispatch(
		const float DeltaTime, const TArray<FTransform>& Transforms
	)
	{
		if (IsInRenderingThread())
		{
			Dispatch(GetImmediateCommandList_ForRenderCommand(), DeltaTime, Transforms);
		}
		else
		{
			DispatchGameThread(DeltaTime, Transforms);
		}
	}

private:
	static void Dispatch(
		FRHICommandListImmediate& RHICmdList,
		const float DeltaTime, const TArray<FTransform>& Transforms
	);

	static void DispatchGameThread(
		const float DeltaTime, const TArray<FTransform>& Transforms
	)
	{
		// TODO: SceneDrawCompletion is sus.  The portal should be part of the scene draw.
		ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
			[DeltaTime, Transforms](FRHICommandListImmediate& RHICmdList)
			{
				Dispatch(RHICmdList, DeltaTime, Transforms);					
			}
		);
	}
};