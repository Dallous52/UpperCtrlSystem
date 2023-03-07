#ifndef _USOCKET
#define _USOCKET

#include "MSocket.h"


class USock : public MSocket
{
public:
	USock(SubmitType submit);
	virtual ~USock() override;

public:
	SOCK ConnectTo() override;

	SOCK BindOrListen() override;

};


#endif // !_USOCK
