// This is the main DLL file.

#include "stdafx.h"
#include "ManagedBES.h"


ManagedBES::ManagedBasylKeyGenerator::ManagedBasylKeyGenerator(String^ pass) : gen(nullptr)
{
	
	IntPtr ip = Marshal::StringToHGlobalAnsi(pass);
	const char* str = static_cast<const char*>(ip.ToPointer());
	string pass2(str);
	Marshal::FreeHGlobal(ip);

	gen = new BasylKeyGenerator(pass2);
}

ManagedBES::ManagedBasylKeyGenerator::ManagedBasylKeyGenerator(String^ pass, int initial, int rounds, int leftoff, int expansion, String^ additionalKey) : gen(nullptr)
{

	IntPtr ip = Marshal::StringToHGlobalAnsi(pass);
	const char* str = static_cast<const char*>(ip.ToPointer());
	string pass2(str);
	Marshal::FreeHGlobal(ip);

	
	ip = Marshal::StringToHGlobalAnsi(additionalKey);
	const char* str2 = static_cast<const char*>(ip.ToPointer());
	string additional(str2);
	Marshal::FreeHGlobal(ip);
	
	gen = new BasylKeyGenerator(pass2, initial, rounds, leftoff, expansion, additional);
}

ManagedBES::ManagedBasylKeyGenerator::ManagedBasylKeyGenerator(String^pass, int initial, int rounds, int leftoff, int expansion, String^ additionalKey, cli::array<byte>^ hash, cli::array<byte>^  key1, cli::array<byte>^ key2, bool encrypted) : gen(nullptr)
{
	IntPtr ip = Marshal::StringToHGlobalAnsi(pass);
	const char* str = static_cast<const char*>(ip.ToPointer());
	string pass2(str);
	Marshal::FreeHGlobal(ip);


	ip = Marshal::StringToHGlobalAnsi(additionalKey);
	const char* str2 = static_cast<const char*>(ip.ToPointer());
	string additional(str2);
	Marshal::FreeHGlobal(ip);


	BasylArray<byte> _hash(hash->Length), _key1(key1->Length), _key2(key2->Length);

	for (int i = 0; i < hash->Length; i++)
	{
		_hash[i] = hash[i];
	}

	for (int i = 0; i < key1->Length; i++)
	{
		_key1[i] = key1[i];
	}

	for (int i = 0; i < key2->Length; i++)
	{
		_key2[i] = key2[i];
	}

	gen = new BasylKeyGenerator(pass2, initial, rounds, leftoff, expansion, additional, _hash, _key1, _key2, encrypted);
}

byte ManagedBES::ManagedBasylKeyGenerator::GetRandomByte()
{
	return gen->GetRandomByte();
}