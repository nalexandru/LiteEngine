#include "DeferredDirectionalLightRenderPass.h"

#include "Managers/ShaderManager.h"

#include "Renderer/Pipeline.h"

DeferredDirectionalLightRenderPass::DeferredDirectionalLightRenderPass () :
	_shaderName ("DIRECTIONAL_LIGHT"),
	_shadowShaderName ("SHADOW_MAP_DIRECTIONAL_LIGHT")
{

}

void DeferredDirectionalLightRenderPass::Init (const RenderSettings& settings)
{
	/*
	 * Shader for general directional light with no shadow casting
	*/

	ShaderManager::Instance ()->AddShader (_shaderName,
		"Assets/Shaders/deferredDirVolLightVertex.glsl",
		"Assets/Shaders/deferredDirVolLightFragment.glsl");

	/*
	 * Shader for directional light with shadow casting
	*/

	ShaderManager::Instance ()->AddShader (_shadowShaderName,
		"Assets/Shaders/deferredDirVolLightVertex.glsl",
		"Assets/Shaders/deferredDirVolShadowMapLightFragment.glsl");
}

void DeferredDirectionalLightRenderPass::Clear ()
{
	/*
	 * Nothing
	*/
}

void DeferredDirectionalLightRenderPass::LockShader (const RenderLightObject* renderLightObject)
{
	/*
	 * Unlock last shader
	*/

	Pipeline::UnlockShader ();

	/*
	 * Lock shader for shadow directional light
	*/

	if (renderLightObject->IsCastingShadows () == true) {
		Pipeline::LockShader (ShaderManager::Instance ()->GetShader (_shadowShaderName));
	}

	/*
	 * Lock general shader for directional light
	*/

	if (renderLightObject->IsCastingShadows () == false) {
		Pipeline::LockShader (ShaderManager::Instance ()->GetShader (_shaderName));
	}
}

std::vector<PipelineAttribute> DeferredDirectionalLightRenderPass::GetCustomAttributes (const RenderSettings& settings) const
{
	std::vector<PipelineAttribute> attributes;

	return attributes;
}