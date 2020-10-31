#include "Tracer.h"
#include "Tracer.cpp"
#include <string>

int main() {

	/*for (int i = 0; i < 10; i++) {*/
	//ShapeModel object { "C:\\Users\\Andrey Strelchenko\\Desktop\\31.radar.txt" };
	//ShapeModel object2{ "C:\\Users\\Andrey Strelchenko\\Desktop\\apophis.txt" };
	ShapeModel object3{ "C:\\Users\\Andrey Strelchenko\\Desktop\\qqw.txt" };
	Tracer<100000, 50> tracer;
	//for (int i = 0; i <= 30; i++) {
	//	std::cout << i << " " << 3.1415926535 / 60.0 * i << " ";
	//	auto [tauZ, yarc] = tracer.Trace(object, 3.1415926535 / 60.0 * i);
	//	std::cout << tauZ << " " << object.CalculateTaus(3.1415926535 / 60.0 * i) << " " << yarc << "\n";
	//	//for (auto [epsilon, tauZ] : object.GetCalculatedTauZ()) {
	//	//	std::cout << epsilon << "\t" << tauZ << "\n";
	//	//}
	//}
	
	for (int j = 0; j < 20; j++) {
		std::cout << "########################\n";
		std::cout << 3.14159265 / 40 * j << " " << object3.CalculateTaus(3.14159265 / 40 * j)<<"\n";
		std::cout << "########################\n";
		for (int i = 0; i < 10; i++) {
			auto [tauZ1, yarc1] = tracer.Trace(object3, 3.14159265 / 40 * j);
			std::cout << tauZ1 << " " << yarc1 << "\n";
		}
		std::cout << "\n";
	}
	

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
	/*for (int j = 0; j < 10; j++) {
		double everageTarqe{ 0. };
		ShapeModel object = ShapeModel{ "C:\\Users\\Andrey Strelchenko\\Desktop\\keopatra.txt" };
		for (int i = 0; i < 100; i++) {
			Tracer<5000, 5000> tracer;
			everageTarqe += tracer.TraceTest(object);
		}
		std::cout << everageTarqe / 100.;
	}*/
	//double a = object.CalculateTaus(0).first;
	//std::cout << object.CalculateTaus(0).first << "\n";

	//ShapeModel object = ShapeModel{ "C:\\Users\\Andrey Strelchenko\\Desktop\\qube.txt" };
	//Tracer<10, 4> t;
	//std::cout << t.TracerTestWithTestEmitter(object);
	//double a = object.CalculateTaus(0).first;
	//std::cout << object.CalculateTaus(0).first << "\n";

}