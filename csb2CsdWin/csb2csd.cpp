#include<iostream>
#include<direct.h>
#include <stdio.h>


extern "C"
{
	#include "../luaLib/lua.h"
	#include "../luaLib/lauxlib.h"
	#include "../luaLib/lualib.h"
	#include "../luaLib/buflib.inl"
	#include"../luaLib/lfs.h"
}

std::string GetCsbPath()
{
	char tempBuf[256] = { 0 };
	FILE* pConfig = nullptr;
	fopen_s( &pConfig,"config.ini", "rb");

	fgets(tempBuf, 256, pConfig);

	fclose(pConfig);

	return tempBuf;

}


int main(int argc, char **argv)
{
	
	//2������lua����
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		std::cout << "Creat Lua State Error !" << std::endl;
		return 1;
	}
	//�������ն������ӡ��Ϣ�����Ǳ�����صģ����򿴲���lua��print��Ϣ
	luaL_openlibs(L);

	/* ע�ắ�� */
	luaL_requiref(L, "buffer", luaopen_buffer, 0);


	luaL_requiref(L, "lfs", luaopen_lfs, 0);
	//luaopen_lfs(L);
	//luaopen_buffer(L);
	//lua_register(L, "average", average);

	//3������lua�ű�
	char tempBuf[256] = { 0 };
	getcwd(tempBuf, 256);
	
	const std::string file = "lily.lua";
	std::string script = file;
	int ret = luaL_dofile(L, script.c_str());
	if (ret)
	{

		std::cout << "Lua doFile Error !" << std::endl;
		return 1;
	}
	lua_getglobal(L, "main");
	lua_newtable(L); // ����һ��table
	lua_pushstring(L, "csbPath");  //keyΪintVal

	std::string csbPath = GetCsbPath();
	lua_pushstring(L, csbPath.c_str());      //ֵΪ1234
	lua_settable(L, -3);          //д��table
	lua_pcall(L, 1, 0, 0);

	lua_close(L);
	system("pause");
	return 0;
}