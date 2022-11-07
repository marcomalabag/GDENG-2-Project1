#include "Shaderlibrary.h"

Shaderlibrary* Shaderlibrary::sharedInstance = NULL;

Shaderlibrary::Shaderlibrary()
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	ShaderData shaderdata;
	ShaderNames names;

	graphEngine->compileVertexShader(names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activeVertexShaders[names.BASE_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderdata.shaderByteCode, shaderdata.sizeShader);

	graphEngine->compilePixelShader(names.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderdata.shaderByteCode, &shaderdata.sizeShader);
	this->activePixelShaders[names.BASE_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderdata.shaderByteCode, shaderdata.sizeShader);
}

Shaderlibrary* Shaderlibrary::getInstance()
{
	return sharedInstance;
}

void Shaderlibrary::initialize()
{
	sharedInstance = new Shaderlibrary();
}

void Shaderlibrary::destroy()
{
	delete sharedInstance;
}

void Shaderlibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
	ShaderNames names;
	ShaderData shaderdata;

	if(vertexShaderName == names.BASE_VERTEX_SHADER_NAME)
	{
		graphEngine->compileVertexShader(names.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", shaderByteCode, sizeShader);
		
	}

	
}

void Shaderlibrary::requestPixelShaderData(String pixelShaderName, void** shaderByteCode, size_t* sizeShader)
{
}

VertexShader* Shaderlibrary::getVertexShader(String vertexShaderName)
{
	return this->activeVertexShaders.at(vertexShaderName);
}

PixelShader* Shaderlibrary::getPixelShader(String pixelShaderName)
{
	return this->activePixelShaders.at(pixelShaderName);
}

Shaderlibrary::~Shaderlibrary()
{
	ShaderNames names;
	this->activeVertexShaders[names.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[names.BASE_PIXEL_SHADER_NAME]->release();

	this->activePixelShaders.clear();
	this->activeVertexShaders.clear();
}
