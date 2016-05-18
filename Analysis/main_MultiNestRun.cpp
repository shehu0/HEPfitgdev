#include <iostream>
#include "ModelFactory.h"
#include "ThObsFactory.h"
#include "MultiNest.h"
#ifdef _MPI   
#include <mpi.h>
#endif

using namespace RooFit;
using namespace RooStats;

int main(int argc, char** argv)
{

#ifdef _MPI
  MPI::Init();
  int rank = MPI::COMM_WORLD.Get_rank();        // current process id 
  int procnum = MPI::COMM_WORLD.Get_size();     // number of processes 
  MPI::Status status;
#else
  int rank = 0;
  int procnum = 1;
#endif

  std::cout << "Hello world from process " << rank+1 << " of " << procnum << std::endl; 

  if(rank == 0) {
    try {

      if(argc != 2){
	std::cout << "\nusage: " << argv[0] << " ModelConf.conf\n" << std::endl;
	return EXIT_SUCCESS;
      }

      std::string ModelConf = argv[1];

      /* Create objects of the classes ModelFactory and ThObsFactory */
      ModelFactory ModelF;
      ThObsFactory ThObsF;

      MultiNest MN(ModelF, ThObsF, ModelConf);
      MN.run();

#ifdef _MPI
      MPI::Finalize();
#endif

      return EXIT_SUCCESS;
      
    } catch (const std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }

}



