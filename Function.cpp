#include "Function.hpp"
#include "Object.hpp"

Variable* Function::evaluate(Variable* parameters) {
	return object.evaluateFunction(functionName, parameters);
}