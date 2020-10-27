#include "Tracer.h"
#include "Tracer.cpp"
#include <string>

int main() {
	try {
		//for (int i = 0; i < 10; i++) {
		//	ShapeModel object = ShapeModel{ "C:\\Users\\Andrey Strelchenko\\Desktop\\keopatra.txt" };

		//	Tracer<2000, 20> tracer;
		//	for (int i = 0; i <= 30; i++) {
		//		tracer.Trace(object, 3.1415926535 / 60.0 * i);
		//		std::cout << i << "\t" << 3.1415926535 / 60.0 * i << "\n";
		//		//for (auto [epsilon, tauZ] : object.GetCalculatedTauZ()) {
		//		//	std::cout << epsilon << "\t" << tauZ << "\n";
		//		//}
		//	}

		//	std::string path = "C:\\Users\\Andrey Strelchenko\\Desktop\\jopa\\";
		//	std::string name = "out" + std::to_string(i) + ".txt";
		//	std::string fullPath = path + name;

		//	std::ofstream output{ fullPath };
		//	for (auto [epsilon, tauZ] : object.GetCalculatedTauZ()) {
		//		output << epsilon << "\t" << tauZ << "\n";
		//		std::cout << epsilon << "\t" << tauZ << "\n";
		//	}
		//	std::cout << "###################";
		//}
		for (int j = 0; j < 10; j++) {
			double everageTarqe{ 0. };
			ShapeModel object = ShapeModel{ "C:\\Users\\Andrey Strelchenko\\Desktop\\keopatra.txt" };
			for (int i = 0; i < 100; i++) {
				Tracer<5000, 5000> tracer;
				everageTarqe += tracer.TraceTest(object);
			}
			std::cout << everageTarqe / 100.;
		}
		//double a = object.CalculateTaus(0).first;
		//std::cout << object.CalculateTaus(0).first << "\n";
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

}