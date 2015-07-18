// ManagedBES.h
#pragma once
using namespace System;

#include <string>
//You may have to modify these paths.
#include "../../BESCPP/BESCPP/BasylKeyGenerator.h"
#include "../../BESCPP/BESCPP/BasylKeyGenerator.cpp"
#include "../../BESCPP/BESCPP/BasylArray.h"
#include "../../BESCPP/BESCPP/BasylArray.cpp"
#include "../../BESCPP/BESCPP/PseudorandomGenerator.h"
#include "../../BESCPP/BESCPP/PseudorandomGenerator.cpp"
//paths end

using namespace System::Runtime::InteropServices;
using namespace std;
namespace ManagedBES {

	public ref class ManagedBasylKeyGenerator
	{
		// TODO: Add your methods for this class here.
	public:
		ManagedBasylKeyGenerator(String^ pass);
		ManagedBasylKeyGenerator(String^ pass, int initial, int rounds, int leftoff, int expansion, String^ additionalKey);
		ManagedBasylKeyGenerator(String^pass, int initial, int rounds, int leftoff, int expansion, String^ additionalKey, cli::array<byte>^ hash, cli::array<byte>^  key1, cli::array<byte>^ key2, bool encrypted);


		~ManagedBasylKeyGenerator()
		{

			this->!ManagedBasylKeyGenerator();
		}

		!ManagedBasylKeyGenerator()
		{
			gen->Key1().Drop();
			gen->Key2().Drop();
			delete gen;
		}

		byte GetRandomByte();

		void Encrypt(byte& b)
		{
			
			gen->Encrypt(b);
		}

	private:
		BasylKeyGenerator* gen;
		
	};

	public ref class ManagedPseudoRandomGenerator
	{
		// TODO: Add your methods for this class here.
	public:
		ManagedPseudoRandomGenerator() :gen(new PseudoRandomGenerator)
		{	
		}

		ManagedPseudoRandomGenerator(int size) : gen(new PseudoRandomGenerator(size))
		{
		}

		ManagedPseudoRandomGenerator(int size, String^ pass) : gen(nullptr)
		{
			IntPtr ip = Marshal::StringToHGlobalAnsi(pass);
			const char* str = static_cast<const char*>(ip.ToPointer());
			gen = new PseudoRandomGenerator(size, string(str));
			Marshal::FreeHGlobal(ip);
		}
		ManagedPseudoRandomGenerator(int size, String^ pass, int rounds) : gen(nullptr)
		{
			IntPtr ip = Marshal::StringToHGlobalAnsi(pass);
			const char* str = static_cast<const char*>(ip.ToPointer());
			gen = new PseudoRandomGenerator(size, string(str), rounds);
			Marshal::FreeHGlobal(ip);
		}

		~ManagedPseudoRandomGenerator()
		{
			this->!ManagedPseudoRandomGenerator();
		}

		!ManagedPseudoRandomGenerator()
		{
			gen->Drop();
			delete gen;
		}

		byte GetRandomByte()
		{
			return gen->GetRandomByte();
		}

		void SetSHA(cli::array<unsigned __int8>^ hash)
		{
			BasylArray<byte> ba(hash->Length);

			for (int i = 0; i < hash->Length; i++)
			{
				ba[i] = hash[i];
			}
			gen->SetSHA(ba);
		}
		
		void SetAdditional(cli::array<unsigned __int8>^ additional)
		{
			BasylArray<byte> ba(additional->Length);

			for (int i = 0; i < additional->Length; i++)
			{
				ba[i] = additional[i];
			}
			gen->SetSHA(ba);
		}


		void SetRecycleKey(String^ pass)
		{
			IntPtr ip = Marshal::StringToHGlobalAnsi(pass);
			const char* str = static_cast<const char*>(ip.ToPointer());
			string pass2(str);
			Marshal::FreeHGlobal(ip);



			gen->SetRecycleKey(pass2);
		}

		void SetLeftoff(int amount)
		{
			gen->SetLeftoff(amount);
		}

		void ExpandKey(int times)
		{
			gen->ExpandKey(times);
		}

		void Recycle()
		{
			gen->Recycle();
		}

		void Drop()
		{
			gen->Drop();
		}
	private:
		PseudoRandomGenerator* gen;
	};
}
