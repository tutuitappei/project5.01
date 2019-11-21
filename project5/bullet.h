#pragma once
#include "Obj.h"
class bullet :
	public Obj
{
public:
	bullet();
	bullet(Vector2db pos);
	void Update(void) override;
	~bullet();
private:
	int Init();
	void destroy();
};

