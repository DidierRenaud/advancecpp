#include "DemoEnum.h"
#include "DemoUtility.h"

using namespace std;
enum class MyColor : char {
	red=1, green, blue 
};
enum class MyHigthResColorRVB : long {
	red = 0xFF0000, green = 0x00FF00, blue = 0x0000FF
};
enum class MyDaltonianFriendColor : long {
	red = 0xFF0000, green = 0x000100, blue = 0x0000FF
};

MyHigthResColorRVB convertColor(MyColor color) {
	switch (color) {
	//case red: // error red is unknown
	case MyColor::red:
		return MyHigthResColorRVB::red; 
	case MyColor::green:
		return MyHigthResColorRVB::green;
	case MyColor::blue:
		return MyHigthResColorRVB::blue;
	}

}

std::ostream& operator<<(std::ostream& os, MyColor c)
{
	switch (c)
	{
		//c++ 20 
		//using enum MyColor;
		case MyColor::red: os << "Low res red " << static_cast<long >(c);    break;
		case MyColor::green: os << "Low res green " << static_cast<long>(c);  break;
		case MyColor::blue: os << "Low res blue " << static_cast<long>(c);   break;
		default: os.setstate(std::ios_base::failbit);
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, MyHigthResColorRVB c)
{
	switch (c)
	{
		//c++ 20 
		//using enum MyColor;
	case MyHigthResColorRVB::red: os << "Hight res red " << std::hex<< static_cast<long>(c);    break;
		case MyHigthResColorRVB::green: os << "Hight res green " << std::hex << static_cast<long>(c) ;  break;
		case MyHigthResColorRVB::blue: os << "Hight res blue " << std::hex << static_cast<long>(c);   break;
		default: os.setstate(std::ios_base::failbit);
	}
	return os;
}

void DemoEnum::runDemo() {
	cout << "Convert " << MyColor::blue << " to " << convertColor(MyColor::blue) << endl;
	cout << "Convert " << MyColor::green << " to " << convertColor(MyColor::green) << endl;
}