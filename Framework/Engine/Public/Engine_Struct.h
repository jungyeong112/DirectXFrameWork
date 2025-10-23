#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_Typedef.h"

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND hWnd;
		WINMODE eMode;
		unsigned int iWinSizeX;
		unsigned int iWinSizeY;
		unsigned int iNumLevels;
	}ENGINE_DESC;

	
	/* D3DDECLUSAGE */
	typedef struct tagVertexPositionTexcoord
	{		
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexcoord;		
	}VTXPOSTEX;

	
}


#endif // Engine_Struct_h__
