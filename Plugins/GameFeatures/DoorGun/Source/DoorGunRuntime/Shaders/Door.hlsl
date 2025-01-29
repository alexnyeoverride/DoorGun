#define PI 3.14159265359;

// TODO:  non-const, because the portal starts small and grows
static const float MAJOR_RADIUS = 100.0; // cm
static const float MINOR_RADIUS = 10.0; // cm

static const uint GRID_WIDTH = uint(MINOR_RADIUS) * 2 + 1;
static const uint GRID_HEIGHT = GRID_WIDTH;
static const uint GRID_LENGTH = uint(MAJOR_RADIUS * 2 * PI);

static const float RENDER_FALLOFF = 1.2;


cbuffer WorldTransform {
	float4x4 quantumToWorld;
	float3 portalCenter;
	float dt;
}

// Get the 6 directly-adjacent voxels, or if at boundary wrap (even for non-toroidal dimensions).
float2 ToroidalLaplacian(float3 pos, RWTexture3D<float2> psi) {
    float2 center = psi.Load(int3(pos));
    float2 laplacian = 0.0;
    
    uint zPlus = (pos.z + 1) % GRID_LENGTH;
    uint zMinus = (pos.z - 1 + GRID_LENGTH) % GRID_LENGTH;
    laplacian += psi.Load(int3(pos.x, pos.y, zPlus));
    laplacian += psi.Load(int3(pos.x, pos.y, zMinus));

	uint yPlus = (pos.y + 1) % GRID_HEIGHT;
	uint yMinus = (pos.y - 1 + GRID_HEIGHT) % GRID_HEIGHT;
	laplacian += psi.Load(int3(pos.x, pos.y, yPlus));
	laplacian += psi.Load(int3(pos.x, pos.y, yMinus));

	uint xPlus = (pos.x + 1) % GRID_WIDTH;
	uint xMinus = (pos.x - 1 + GRID_WIDTH) % GRID_WIDTH;
	laplacian += psi.Load(int3(pos.x, pos.y, xPlus));
	laplacian += psi.Load(int3(pos.x, pos.y, xMinus));
    
    laplacian -= 6.0 * center;
    // simplified, do not divide by square of cell size, which is just 1.

    return laplacian;
}

[numthreads(8, 8, 8)]
void Tick(uint3 id : SV_DispatchThreadID, RWTexture3d<float2> psi, RWTexture3d<float2> psi_next)
{
	float3 pos = float3(id);
	float2 current_psi = psi[id];
	float2 laplacian = ToroidalLaplacian(pos, psi);

	// Simplified hamiltonian with hbar and mass == 1.
	float2 hamiltonian_psi = float2(
		-laplacian.x / 2,
		-laplacian.y / 2
	);

	float2 next_psi = current_psi + hamiltonian_psi * dt;
	psi_next[id] = next_psi;
}















// Rendering

float SignedDistanceTorus(float3 p)
{
	float planar_dist = length(float2(p.x, p.z)) - R;
	return length(float2(planar_dist, p.y)) - r;
}


// Convert quantum coordinates to volumetric torus space
float3 QuantumToTorusVolume(float3 qPos) {
    // Map x,y to cross-section position (-1 to 1)
    float2 crossSection = float2(
        (qPos.x / GRID_WIDTH) * 2.0 - 1.0,
        (qPos.y / GRID_HEIGHT) * 2.0 - 1.0
    );
    
    // Map z to angle around major radius (0 to 2π)
    float theta = (qPos.z / GRID_LENGTH) * 2.0 * PI;
    
    // Calculate center point of the circular cross-section, lying on the circumference of the major circle.
    float3 crossSectionCenter = float3(
        MAJOR_RADIUS * cos(theta),
        0,
        MAJOR_RADIUS * sin(theta)
    );
    
    // Calculate final position by offsetting from cross-section center
    return float3(
        crossSectionCenter.x + crossSection.x * MINOR_RADIUS * cos(theta),
        crossSection.y * MINOR_RADIUS,
        crossSectionCenter.z + crossSection.x * MINOR_RADIUS * sin(theta)
    );
}


void Render(uint3 id : SV_DispatchThreadID, RWTexture3D<float4> output, RWTexture3D<float2> psi) {
    float3 qPos = float3(id);
    float2 wavefunction = psi[id];
    float probability = dot(wavefunction, wavefunction);
    
    float3 torusPos = QuantumToTorusVolume(qPos);    
    float4 worldPos = mul(quantumToWorld, float4(torusPos, 1.0));
    worldPos.xyz += portalCenter;
    
    output[id] = color;
}