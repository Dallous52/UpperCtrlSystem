#ifndef _TSOCKET
#define _TSOCKET

#include "MSocket.h"


class TSock : public MSocket
{
public:
	TSock(SubmitType submit);
	virtual ~TSock() override;

public:
	SOCK ConnectTo() override;

	SOCK BindOrListen() override;

};


#endif // !_USOCK
