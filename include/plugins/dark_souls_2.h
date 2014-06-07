#pragma once

#include "game_plugin.h"

#include "smaa.h"
#include "ssao.h"
#include "fxaa.h"
#include "dof.h"
#include "post.h"
#include "bloom.h"

class DS2Plugin : public GamePlugin {

	IDirect3DStateBlock9* defaultState;
	IDirect3DSurface9 *zBufferSurf, *hdrRT;
	bool aaStepStarted, aoDone;
	DOF* dof;
	SSAO* ssao;
	Post* post;
	FXAA* fxaa;
	SMAA* smaa;
	Bloom* bloom;
	bool doDof, doAO, doPost, doAA, doBloom;

public:
	DS2Plugin(IDirect3DDevice9* device, RSManager &manager) : GamePlugin(device, manager)
		, defaultState(NULL), zBufferSurf(NULL), hdrRT(NULL)
		, aaStepStarted(false), aoDone(false)
		, dof(NULL), ssao(NULL), post(NULL)
		, fxaa(NULL), smaa(NULL), bloom(NULL)
		, doAO(true), doDof(true), doPost(true), doAA(true), doBloom(true)
	{ }

	virtual ~DS2Plugin();

	virtual void initialize(unsigned rw, unsigned rh);
	virtual void reportStatus();

	virtual void prePresent();

	virtual HRESULT redirectSetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget);
	virtual HRESULT redirectSetPixelShader(IDirect3DPixelShader9* pShader);
	virtual HRESULT redirectDrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
	virtual HRESULT redirectSetRenderState(D3DRENDERSTATETYPE State, DWORD Value);

	virtual void toggleAA() { if(smaa || fxaa) { doAA = !doAA; Console::get().add(doAA ? "AA enabled" : "AA disabled"); } else { Console::get().add("AA disabled in configuration!"); } }
	virtual void toggleAO() { if(ssao) { doAO = !doAO; Console::get().add(doAO ? "SSAO enabled" : "SSAO disabled"); } else { Console::get().add("SSAO disabled in configuration!"); } }
	virtual void toggleDOF() { if(dof) { doDof = !doDof; Console::get().add(doDof ? "DoF enabled" : "DoF disabled"); } else { Console::get().add("DoF disabled in configuration!"); } }
	virtual void toggleBloom() { if(bloom) { doBloom = !doBloom; Console::get().add(doBloom ? "Bloom enabled" : "Bloom disabled"); } else { Console::get().add("Bloom disabled in configuration!"); } }
	virtual void togglePost() { if(post) { doPost = !doPost; Console::get().add(doPost ? "Post-processing enabled" : "Post-processing disabled"); } else { Console::get().add("Post-processing disabled in configuration!"); } }
};