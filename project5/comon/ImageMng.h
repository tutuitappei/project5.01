#pragma once
#include <memory>
#include <map>
#include <vector>
#include <Vector2.h>
#include <string>

using  VecInt = std::vector<int>;



#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetId(KEY))	

class ImageMng
{

public:
	static ImageMng &GetInstance(void)	//実体を、呼び出す？処理
	{
		return *sInstance;
	}

	const  VecInt& GetId(const std::string& key);								//キーで取り出す。
	const  VecInt& GetId(const std::string& key,const std::string filename);	//キーと、ファイル名で取り出す。
	const  VecInt& GetId(const std::string& key, const std::string filename,	//キーとファイル名、サイズと枚数を指定
						const Vector2in divsize, const Vector2in divcont);

private:
	struct ImageMngDeleter				//カスタムデリータ
	{
		void operator()(ImageMng* imageMng)const
		{
			delete imageMng;
		}
	};

	ImageMng();
	~ImageMng();
	static std::unique_ptr<ImageMng, ImageMngDeleter> sInstance;

	std::map<std::string, VecInt> imgMap;		//読み込んだイメージデータが格納される.


};

