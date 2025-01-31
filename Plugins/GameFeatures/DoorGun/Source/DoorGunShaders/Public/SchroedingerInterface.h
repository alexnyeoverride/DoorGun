#pragma once

class DOORGUNSHADERS_API FSchroedingerInterface
{
public:
	static void Initialize();
	static void Dispatch(
		const float DeltaTime, const TArray<FTransform>& Transforms
	);
	static void CleanUp()
	{
		if (PersistentPing.IsValid())
		{
			PersistentPing.SafeRelease();
		}
		if (PersistentPong.IsValid())
		{
			PersistentPong.SafeRelease();
		}
	}

private:
	static void Initialize(FRHICommandListImmediate& RHICmdList);
	static void Dispatch(
		FRHICommandListImmediate& RHICmdList,
		const float DeltaTime, const TArray<FTransform>& Transforms
	);

	// A texture is not released on the GPU until the application specifically requests it, but Unreal does a lot of memory management.
	// This texture will not be copied back to the CPU.  Hold on to the handle to ensure the memory is valid.
	static TRefCountPtr<IPooledRenderTarget> PersistentPing;
	static TRefCountPtr<IPooledRenderTarget> PersistentPong;
	static bool PingPong;
};