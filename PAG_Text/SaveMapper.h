#pragma once
#include "SaveFile.h"

class SaveMapper
{
	public:
		static void SetAteTrash(bool);


	private:
		static void SetByteAt(SaveFile, int byte, int address);
		static void ORByteAt(SaveFile, int byte, int address);
		static void ANDByteAt(SaveFile, int byte, int address);
		static void SetBitAt(SaveFile, int pos, int address);
		static void UnsetBitAt(SaveFile, int pos, int address);
};

