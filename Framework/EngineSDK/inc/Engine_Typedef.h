#ifndef Engine_Typedef_h__
#define Engine_Typedef_h__

namespace Engine
{
	typedef		bool						_bool;

	typedef		signed char					_byte;
	typedef		unsigned char				_ubyte;
	typedef		char						_char;

	typedef		wchar_t						_tchar;
	typedef		wstring						_wstring;
	
	typedef		signed short				_short;
	typedef		unsigned short				_ushort;

	typedef		signed int					_int;
	typedef		unsigned int				_uint;

	typedef		signed long					_long;
	typedef		unsigned long				_ulong;

	typedef		float						_float;
	typedef		double						_double;

	typedef		D3DXVECTOR2					_float2;
	typedef		D3DXVECTOR3					_float3;
	typedef		D3DXVECTOR4					_float4;

	typedef		D3DXMATRIX					_float4x4;

	//typedef struct MyVector final : public D3DXVECTOR3
	//{
	//	void normalize();
	//	float length();
	//	float distance(MyVector vTarget);
	//}_float3;

	




}

#endif // Engine_Typedef_h__
