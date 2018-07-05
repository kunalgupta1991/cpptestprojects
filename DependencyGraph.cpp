#include"LockFreeQueue.cpp"
//using namespace pandocode;
namespace pandocode
{
	enum class DGstate : int
	{
		unresolved = 0,
		resolved = 1,
		done =2
	};
	typedef long long JobID;
	class DependencyGraph
	{
	public :
		explicit DependencyGraph()
		{

		}
		DependencyGraph(const DependencyGraph &) = delete;
		DependencyGraph(DependencyGraph &&) = delete;
		bool initialize(JobID start, JobID end)
		{

		}
		vector<JobID> GetDependents(JobID jobid)
		{

		}
		bool isJobresolved(JobID jobid)
		{

		}
		
		bool IsGraphResolved()
		{

		}
		bool InsertJob(JobID job, JobID dependingJob, JobID dependantJob)
		{

		}//Insert 1 job between dependingJob and dependantJob.
		bool InsertJobs(vector<JobID> jobs, JobID dependingJob, JobID dependantJob)
		{

		}//Insert n jobs between dependingJob and dependantJob.
		bool InsertJobs(vector<JobID> jobs, JobID dependingJob)
		{

		}//Insert n jobs between dependingJob and all its dependants.
		bool createNode(JobID job)
		{
			if (DG.find(job) == DG.end())
			{
				unique_ptr<Node>startNode = make_unique<Node>(job);
				//startNode->state = DGstate::done;
				//numOfDoneNodes++;
				DG[job] = std::move(startNode);
				return true;
			}
			else
				return false;
		}
		bool createStartNode(JobID job)
		{
			if (DG.find(job) == DG.end())
			{
				unique_ptr<Node>startNode = make_unique<Node>(job);
				startNode->state = DGstate::done;
				numOfDoneNodes++;
				DG[job] = std::move(startNode);
				return true;
			}
			else
				return false;
		}
		bool connectStartAndEnd(JobID job1, JobID job2)
		{
			auto itrjob1 = DG.find(job1);
			auto itrjob2 = DG.find(job2);
			if (itrjob1 == DG.end() || itrjob2 == DG.end())
				return false;
			Node* jobNode1 = itrjob1->second.get();
			Node* jobNode2 = itrjob2->second.get();
			jobNode1->dependents[job2] = jobNode2;
			jobNode2->num_of_incoming_dependency++;
		}
		bool disconnectDependency(JobID job1, JobID job2)
		{
			auto itrjob1 = DG.find(job1);
			auto itrjob2 = DG.find(job2);
			if (itrjob1 == DG.end() || itrjob2 == DG.end())
				return false;
			Node* jobNode1 = itrjob1->second.get();
			Node* jobNode2 = itrjob2->second.get();
			auto itr = jobNode1->dependents.find(job2);
			if (itr!= jobNode1->dependents.end())
			{
				jobNode1->dependents.erase(job2);
				jobNode2->num_of_incoming_dependency--;
				return true;
			}
			return false;
		}
		bool connectDependency(JobID Job1, JobID Job2)
		{
			auto itrjob1 = DG.find(Job1);
			auto itrjob2 = DG.find(Job2);
			if (itrjob1 == DG.end() || itrjob2 == DG.end())
				return false;
			Node* jobNode1 = itrjob1->second.get();
			Node* jobNode2 = itrjob2->second.get();
			jobNode1->dependents[Job2] = jobNode2;
			jobNode2->num_of_incoming_dependency++;
			if (jobNode1->state == DGstate::done ) {
				jobNode2->count_of_resolved_dependency++;
				if (jobNode2->count_of_resolved_dependency == jobNode2->num_of_incoming_dependency)
					jobNode2->state = DGstate::resolved;
				_resovedNode.push(jobNode2);
			}
		}
		bool notifyCompletion(JobID job)
		{
			auto itr = DG.find(job);
			if (itr != DG.end())
			{
				Node* node = itr->second.get();
				node->state = DGstate::done;
				numOfDoneNodes++;
				for (auto it : node->dependents) {
					it.second->count_of_resolved_dependency++;
					if (it.second->count_of_resolved_dependency == it.second->num_of_incoming_dependency)
					{
						if (it.second->jobId == 9999)
						{
							it.second->state = DGstate::done;
							numOfDoneNodes++;
						}
						else
						{
							it.second->state = DGstate::resolved;
							_resovedNode.push(it.second);
						}
					}
				}
			}
			else
			{
				return false; //throw exception?
			}

			return true;
		}

	private:
		class Node
		{
		public:
			JobID jobId;
			DGstate state;
			int num_of_incoming_dependency;
			int count_of_resolved_dependency;
			std::map<JobID, Node *> dependents;
			Node(JobID job) : jobId(job), state(DGstate::unresolved), num_of_incoming_dependency(0), count_of_resolved_dependency(0)
			{

			}

		};
		map<JobID, unique_ptr<Node>> DG;
		int numOfDoneNodes;
		LockFreeQueue<Node *> _resovedNode;
	};
};