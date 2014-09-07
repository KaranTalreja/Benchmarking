/*
 * IO.cpp
 *
 *  Created on: 06-Sep-2014
 *      Author: hp
 */
#include "IO.hpp"

void Utils::IO::inp( int &n )//fast input function
{
	n=0;
	register int ch=getcx();int sign=1;
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}

	while(  ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
	n=n*sign;
}

