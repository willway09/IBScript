std::string infixToPostfix(std::string *in, Operator *queue, int queueLen, int min, int max) {
	int index = -1;
	Operator op;
	
	for(int i = queueLen - 1; i >= 0; i--) {
		if(queue[i].index >= min && queue[i].index <= max) {
			op = queue[i];
			index = i;
			
			//std::cout << "Breaking: " << op.type << std::endl;
			
			break;
		}			
	}
	
	if(index != -1) {
		deleteFromQueue(queue, queueLen, index);
		
		return infixToPostfix(in, queue, queueLen, min, op.index - 1) + " " + 
			infixToPostfix(in, queue, queueLen, op.index + 1, max) + " " + 
			op.type + " ";
	} else {
		std::string rtn = "";
		
		for(int i = min; i <= max; i++) {
			
			if(in[i].compare("(") && in[i].compare(")")) {
				rtn += in[i];
			}
		}
		
		return rtn;
	}
}

void infixToPostfix() {
	
	std::cout << "Input infix: ";
	
	std::string in;
	std::getline(std::cin, in);
	
	int idx = 0;
	int spaceCount = -1;
	while(true) {
		spaceCount++;
		idx = in.find(" ", idx);
		if(idx == -1) break;
		idx = idx + 1;
	}
	
	//std::cout << "Token Size: " << spaceCount + 1<< std::endl;
	
	std::string *tokens = new std::string[spaceCount + 1];
	
	idx = 0;
	
	for(int i = 0; i < spaceCount; i++) {
		int nidx = in.find(" ", idx);
		tokens[i] = in.substr(idx, nidx - idx);
		idx = nidx + 1;
	}
	
	tokens[spaceCount] = in.substr(idx, in.size() - idx);
	
	int operatorCount = 0;
	
	/*for(int i = 0; i < spaceCount + 1; i++) {
		std::cout << tokens[i] << "&" << std::endl;
	}*/

	int parenCount = 0;
	
	for(int i = 0; i < spaceCount + 1; i++) {
		
		try {
			std::stof(tokens[i]);
		} catch(std::invalid_argument) {
			
			if(!tokens[i].compare("(") || !tokens[i].compare(")")) {
				parenCount++;
			} else {
				operatorCount++;	
			}
		}
	}
	
	Operator *ops = new Operator[operatorCount];
	
	
	int opIdx = 0;
	int depth = 0;
	for(int i = 0; i < spaceCount + 1; i++) {
		
		try {
			std::stof(tokens[i]);
		} catch(std::invalid_argument) {
			
			if(!tokens[i].compare("(")) {
				depth++;
			} else if(!tokens[i].compare(")")) {
				depth--;
			} else {			
				ops[opIdx].setup(i, depth, tokens[i]);
				/*std::cout << ops[opIdx].type << " ";
				std::cout << ops[opIdx].precedence << " ";
				std::cout << ops[opIdx].index << " ";
				std::cout << ops[opIdx].depth << std::endl;*/
				opIdx++;
			}
		}
	}

	
	//std::cout << "=====================" << std::endl;
	
	Operator *sortedOps = mergeSort(ops, 0, operatorCount - 1, operatorCount);
	
	for(int i = 0; i < operatorCount; i++) {
		/*std::cout << sortedOps[i].type << " ";
		std::cout << sortedOps[i].precedence << " ";
		std::cout << sortedOps[i].index << " ";
		std::cout << sortedOps[i].depth << std::endl;*/
	}
	
	std::string postfix = infixToPostfix(tokens, sortedOps, operatorCount, 0, spaceCount);
	
	std::cout << "Postfix: " << postfix << std::endl;
	evaluatePostfix(postfix);
	//std::cout << std::endl;
	
	delete[] tokens;
	delete[] ops;
	delete[] sortedOps;
	
}