#include <iostream>
#include <vector>
#include <string>

enum Colors { red, yellow, green };
//enum SemColors { red, yellow, orange, green };
enum class SemaphorColors { red, yellow, green };

class Semaphor {
private:
	std::vector<std::string> alerts = { "Stop", "Attenzione", "Avanti" };
	SemaphorColors color = SemaphorColors::red;
public:
	using enum SemaphorColors;

	std::string alert() { return alerts[static_cast<int>(color)]; }
	void change() {
		switch (color)
		{
		case SemaphorColors::red:color = SemaphorColors::green;
			break;
		case SemaphorColors::yellow:color = Semaphor::red;
			break;
		case SemaphorColors::green:color = Semaphor::yellow;
			break;
		default:
			break;
		}
	}
	friend std::ostream& operator<<(std::ostream& s, const Semaphor& se) {
		return s << (se.color == Semaphor::red ?
			"rosso" : se.color == se.green ? "verde" : "giallo");
	}
};
int main()
{
	std::cout << red << '\t' << yellow << '\t' << green << std::endl;
	Colors c = yellow;
	std::cout << c << std::endl;
	std::cout << static_cast<int>(SemaphorColors::red) << std::endl;
	auto s = Semaphor{};
	for (auto i = 0; i < 4; ++i)
	{
		s.change();
		std::cout << s << '\t' << s.alert() << '\t' << static_cast<int>(Semaphor::red) << 
			'\t' << static_cast<int>(s.red) <<std::endl;
	}

}
