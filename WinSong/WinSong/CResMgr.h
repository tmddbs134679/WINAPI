#pragma once

class CTexture;
class CRes;

class CResMgr
{
	SINGLE(CResMgr);



public:
		//키값으로 wstring
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);

private:

	map<wstring, CRes*>	m_mapTex;

};

