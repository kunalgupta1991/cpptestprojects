#include < iostream>
#include < list>
#include < vector>
#include <memory>
#include <mutex>
#include < deque>
using namespace std;
struct listNode
{
	int d;
	int weight;
};
class Graph
{
	list <listNode > * adj;
	//vector< list<int> > ;
	int v;
	int * indegree;
public :
	Graph(int V)
	{
		v = V;
		adj = new list<listNode>[V];
		indegree = new int[V];
		for (int i = 0; i < V; i++)
			indegree[i] = 0;
	}
	void addedge(int s, int d, int w)
	{
		adj[s].push_back({d,w});
		indegree[d]++;
		adj[d].push_back({ s,w });

	}
	void digik(int s);
	void digik_stl(int s);
};
struct heapNode
{
	int v;
	int distance;
	bool operator<(heapNode &rhs)
	{
		return distance < rhs.distance;
	}
};
class heap
{
	
	int size;
	int capacity;
	vector<heapNode> arr;
	vector<int> pos;
public :
	heap(int V)
	{
		size = V;
		capacity = V;
		arr =  vector<heapNode>(V);
		pos = vector<int>(V);
		for (int i = 0; i < V; i++)
		{
			arr[i].v = i;
			arr[i].distance = 1000;
			pos[i] = i;
		}
	}
	void heapify(int i)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int min=i;
		if (left < size)
		{
		
		min = arr[i] < arr[left] ? i : left;
	}
		if (right < size)
		{
			min = arr[min] < arr[right] ? min : right;
		}
		if (min != i)
		{
			heapNode temp = arr[min];
			pos[arr[i].v] = min;
			pos[arr[min].v] = i;
			arr[min] = arr[i];
			arr[i] = temp;
			
			heapify(min);
		}

		

	}
	 heapNode extractmin()
	{
		 if (size < 0)
			 return heapNode{ -1,-1 };
		 heapNode temp = arr[0];
		 pos[arr[0].v] = size - 1;
		 pos[arr[size - 1].v] = 0;
		 arr[0] = arr[size - 1];
		 arr[size - 1] = temp;
		
		 size = size - 1;
		 heapify(0);
		 return temp;

	}
	 void createHeap()
	 {
		 for (int i = size / 2; i >= 0; i--)
			 heapify(i);
	 }
	void  pushelement(heapNode hn)
	 {

	 }
	void setDistance(int i, int distance)
	{
		arr[pos[i]].distance = distance;
		
	}
	bool isempty()
	{
		return size <= 0;
	}
 void updateDistance(int v, int distance)
	{
		int i = pos[v];
		arr[i].distance = distance;
		//i = i - 1 / 2;
		while (i&&arr[i].distance < arr[(i-1)/2].distance)
		{
			heapNode temp = arr[(i - 1) / 2];
			pos[arr[i].v] = i - 1 / 2;
			pos[arr[(i - 1) / 2].v] = i;
			arr[(i - 1) / 2] = arr[i];
			arr[i] = temp;;
			
			i = (i - 1) / 2;
		}
	}
};
void Graph::digik(int s)
{
	vector<int> dist(v,1000);
	heap h(v);
	h.setDistance(s, 0);
	dist[s] = 0;
	h.createHeap();
	vector<bool>visited(v, false);
	visited[s] = true;
	while (!h.isempty())
	{
		heapNode u = h.extractmin();
		visited[u.v] = true;
		for (auto itr = adj[u.v].begin(); itr != adj[u.v].end(); itr++)
		{
			if (visited[itr->d] == false)
			{
				if (dist[itr->d] > dist[u.v] + itr->weight)
				{
					h.updateDistance(itr->d, dist[u.v] + itr->weight);
					dist[itr->d] = dist[u.v] + itr->weight;
				}

			 }
		}
	}

	for (int i = 0; i < v; i++)
	{
		cout << dist[i] << " ";
	}
}
void Graph::digik_stl(int s)
{

}
struct functor
{
	void operator() ()
	{
		cout << "functor called";
	}
};

class abc
{
	ostream f;
public :
	/*void print(string s)
	{
		f << s;
	}*/
	
};
//
//int main()
//{
//	functor();
//	
//
//	/*int V = 9;
//	Graph g(V);
//	g.addedge( 0, 1, 4);
//	g.addedge( 0, 7, 8);
//	g.addedge( 1, 2, 8);
//	g.addedge( 1, 7, 11);
//	g.addedge( 2, 3, 7);
//	g.addedge( 2, 8, 2);
//	g.addedge( 2, 5, 4);
//	g.addedge( 3, 4, 9);
//	g.addedge( 3, 5, 14);
//	g.addedge( 4, 5, 10);
//	g.addedge( 5, 6, 2);
//	g.addedge( 6, 7, 1);
//	g.addedge( 6, 8, 6);
//	g.addedge( 7, 8, 7);
//	g.digik(0);
//
//	const char *  name = " hello";
//	name = " kunal";
//*/
//	//cout << c << endl;
//
//

//}
mutex mumu;
int i;
deque<int> dq;
condition_variable condlm;
//void fun2()
//{
//	while (1)
//	{
//		std::unique_lock<mutex> locker(mumu);
//		condlm.wait(locker, []() {return !dq.empty(); });
//			cout << "int consmer " << dq.back() << endl;
//			dq.pop_back();
//			locker.unlock();
//		
//	}
//
//}
//void fun1()
//{
//	int i=0;
//	while (1)
//	{
//		unique_lock	<mutex> ul(mumu);
//		dq.push_front(i);
//		cout << "pushing" << i << endl;
//		condlm.notify_one();
//		ul.unlock();
//	    this_thread::sleep_for(chrono::milliseconds(500));
//		i++;
//	}
//}
//int main()
//{
//	//mukunal.unlock();
//	thread t1(fun1);
//	thread t2(fun2);
//	t1.join();
////	t2.join();
//}