#pragma once
#include <memory>

class BaseScene;	//クラスを、宣言する。

using unique_Base = std::unique_ptr<BaseScene>;		//unique_Baseと、うつと、std::uni～～に、返還されて使える
	
class BaseScene
{
public:
	
	BaseScene();	//コンストラクト

	virtual unique_Base Update(unique_Base own) = 0;	//シーンを、更新する。

	virtual ~BaseScene();	//デコンストラクトを、仮想化する
};

