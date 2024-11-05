#include <string>

class Item {
public:
	Item(const std::string name);

	const std::string getName();

protected:
	const std::string name;
};