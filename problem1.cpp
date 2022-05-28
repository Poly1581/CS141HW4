#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>

#define tMin 0 							//		CONTAINER SIZES		//
#define tMax 10
#define sMin 0
#define sMax 7
#define fMin 0
#define fMax 4
#define total 11

using namespace std;
using vertex = vector<int>;
vector<int> capacity = {tMax,sMax,fMax};

bool fullEdge(vertex& fromVertex, vertex& toVertex) {
	bool fullVertexCondition = false;
	int fullVertexIndex = 0;
	for(int i = 0; i < fromVertex.size(); i++) {
		//	FIND INCREASED TO FULL VERTEX
		if(toVertex.at(i) == capacity.at(i) && toVertex.at(i) > fromVertex.at(i)) {
			fullVertexIndex = i;
			fullVertexCondition = true;
		}
	}

	if(!fullVertexCondition) {
		return false;
	}

	for(int i = 0; i < 3; i++) {
		if(fromVertex.at(i) == toVertex.at(i) && i != fullVertexIndex) {
			return true;
		}
	}

	return false;

}

bool emptyEdge(vertex& fromVertex, vertex& toVertex) {
	bool emptyVertexCondition = false;
	int emptyVertexIndex = 0;
	for(int i = 0; i < 3; i++) {
		if(toVertex.at(i) == 0 && toVertex.at(i) < fromVertex.at(i)) {
			emptyVertexIndex = i;
			emptyVertexCondition = true;
		}
	}

	if(!emptyVertexCondition) {
		return false;
	}

	for(int i = 0; i < 3; i++) {
		if(fromVertex.at(i) == toVertex.at(i) && i != emptyVertexIndex) {
			return true;
		}
	}

	return false;
}

bool checkEdge(vertex& fromVertex, vertex& toVertex) {
	return fullEdge(fromVertex, toVertex)||emptyEdge(fromVertex, toVertex);
}

int main() {
	//			INITIALIZE VERTICES			//
	vertex start = {0,sMax,fMax};										//		STARTING toVertex		//
	int startIndex = 0;
	vector<vertex> vertices;
	for(int t = tMin; t <= tMax; t++) {
		for(int s = sMin; s <= sMax; s++) {
			for(int f = fMin; f <= fMax; f++) {
				if(t+s+f == total) {
					vertex currVertex = {t,s,f};
					vertices.push_back(currVertex);
					if(currVertex == start) {
						startIndex = vertices.size()-1;
					}
				}
			}
		}
	}

	cout << "VERTICES: " << vertices.size() << endl;


	//			INITIALIZE EDGES			//
	vector<vector<bool>> edges(
		vertices.size(),
		std::vector<bool>(
			vertices.size(),
			false)
	);
	for(int fromIndex = 0; fromIndex < vertices.size(); fromIndex++) {
		vertex& fromVertex = vertices.at(fromIndex);
		for(int toIndex = 0; toIndex < vertices.size(); toIndex++) {
			vertex& toVertex = vertices.at(toIndex);
			edges.at(fromIndex).at(toIndex) = checkEdge(fromVertex, toVertex);
		}
	}


	//			DFS						//
	//		NOTE THAT THE STATE IS PATH INVARIANT, AND SO WE CAN AVOID REVISITING NODES FOR ANY REASON	//
	//		AS SUCH, THE QUEUE WILL BE COMPOSED OF INTEGERS REPRESENTING THE INDEX OF THE VERTEX 		//
	vector<int> visited(vertices.size(), false);
	vector<int> previous(vertices.size(), -1);
	queue<int> Q;
	Q.push(startIndex);
	while(!Q.empty()) {
		int currIndex = Q.front();
		Q.pop();
		if(vertices.at(currIndex).at(1) == 2 || vertices.at(currIndex).at(2) == 2) {								//			STOPPING CONDITION 			//
			cout << "PATH FOUND:" << endl;
			stack<int> S;
			while(currIndex != -1) {
				S.push(currIndex);
				currIndex = previous.at(currIndex);
			}
			while(!S.empty()) {
				int currIndex = S.top();
				vertex currVertex = vertices.at(currIndex);
				S.pop();
				cout << "(" << currVertex.at(0) << "," << currVertex.at(1) << "," << currVertex.at(2) << ")" << endl;
			}
			break;
		}
		visited.at(currIndex) = true;
		vector<bool>& currEdges = edges.at(currIndex);
		for(int nextIndex = 0; nextIndex < currEdges.size(); nextIndex++) {
			if(currEdges.at(nextIndex) && !visited.at(nextIndex)) {
				previous.at(nextIndex) = currIndex;
				visited.at(nextIndex) = true;
				Q.push(nextIndex);
			}
		}
	}
}