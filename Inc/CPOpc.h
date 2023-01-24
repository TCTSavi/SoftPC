#ifndef _CPOPC_H_
#define _CPOPC_H_

#include <tchar.h>
#include <stdint.h>

class CPOpc {
	public:
		WCHAR 		*Nome;
		uint8_t		Address;
		uint16_t 	Valor;	
	public:
		CPOpc();		
};

#endif