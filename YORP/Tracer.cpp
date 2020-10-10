#include "Tracer.h"

template<size_t number>
void Tracer<number>::Trace(RayEmitter<number>& emitter) {
	while (!emitter.rays.empty()) {
		for (std::list<Ray>::iterator current = emitter.rays.begin();
			current != emitter.rays.end(); current++) {
			if()/*intersection*/
			emitter.rays.erase(current);
		}
	}
}


