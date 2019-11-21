#include "ImageMng.h"
#include <DxLib.h>


//ImageMng* ImageMng::sInstance = nullptr;
std::unique_ptr<ImageMng,ImageMng::ImageMngDeleter> ImageMng::sInstance(new ImageMng());

const VecInt & ImageMng::GetId(const std::string & key)
{
	return GetId(key, key);
}

const VecInt & ImageMng::GetId(const std::string & key, const std::string filename)
{
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(filename.c_str());
	}
	return imgMap[key];
}

const VecInt & ImageMng::GetId(const std::string & key, const std::string filename, const Vector2in divsize, const Vector2in divcont)
{
	if (imgMap.find(key) == imgMap.end())
	{
	
		imgMap[key].resize(divcont.x*divcont.y);
		LoadDivGraph(filename.c_str(),divcont.x*divcont.y, divcont.x, 
			divcont.y, divsize.x, divsize.y,&imgMap[key][0]);

		//別のやり方
		//VecInt tmpdata;
		//tmpdata.resize(divcont.x*divcont.y);
		//if (LoadDivGraph(filename.c_str(), divcont.x*divcont.y, divcont.x,
		//	divcont.y, divsize.x, divsize.y, &tmpdata[0]) == 0)		//tmpdataに、読み込む
		//{
		//	imgMap[key] = std::move(tmpdata);	//所有権を渡す。
		//}
		//else
		//{
		//	return std::move(tmpdata);		//失敗した場合、所有権を、外側に渡す。
		//}
		//return imgMap[key];

	}
	return imgMap[key];
}

ImageMng::ImageMng()
{
	
}

ImageMng::~ImageMng()
{
}

