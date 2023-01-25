#include <utils.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <map>

using namespace std;
using namespace std::chrono;
using namespace vectorpack;

std::string format_algo_list(const vector<string> & list)
{
    if (list.size() == 0)
    {
        return "[]";
    }

    std::string s("[");
    s+= *(list.begin());
    for (auto it=list.begin()+1; it != list.end(); ++it)
    {
        s+= ", " + *it;
    }
    s+= "]";
    return s;
}

std::string run_for_instance(const Instance & instance,
                             const vector<string> & list_centric,
                             const vector<string> & list_pairing,
                             const vector<string> & list_WFDm)
{
    int LB = LB_BPP(instance);

    int hint_bin = LB + 50;
    int sol;

    string row(to_string(LB));
    string row_res;
    string row_time;
    for (const string & algo_name : list_centric)
    {
        BaseAlgo * algo = createAlgoCentric(algo_name, instance);

        auto start = high_resolution_clock::now();
        sol = algo->solveInstance(hint_bin);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        row_res.append("\t" + to_string(sol));
        row_time.append("\t" + to_string((float)duration.count()));

        delete algo;
    }

    // Compute upper bound for Multibin algos
    BaseAlgo * algoFF = createAlgoCentric("FF", instance);
    int UB = algoFF->solveInstance(hint_bin);
    delete algoFF;

    for (const string & algo_name : list_WFDm)
    {
        AlgoWFDm * algo = createAlgoWFDm(algo_name, instance);

        auto start = high_resolution_clock::now();
        sol = algo->solveInstanceMultiBin(LB, UB);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        row_res.append("\t" + to_string(sol));
        row_time.append("\t" + to_string((float)duration.count()));

        delete algo;
    }

    return row + row_res + row_time;
}

void run_BPPLIB(string& data_path, string& output_path,
                const vector<string> list_centric,
                const vector<string> list_WFDm,
                const map<string, string> map_rename_algos,
                string mode)
{
    data_path += "BPPLIB/";

    vector<string> benchmark_list = {
        "Difficult_Instances",
        "Falkenauer",
        "Hard28",
        "Irnich_BPP",
        "Scholl",
        "Schwerin",
        "Waescher"
    };

    if (mode == "B1")
    {
        benchmark_list.clear();
        benchmark_list.push_back("Difficult_Instances");
    } else if (mode == "B2"){
        benchmark_list.clear();
        benchmark_list.push_back("Falkenauer");
        benchmark_list.push_back("Hard28");
        benchmark_list.push_back("Waescher");
    } else if (mode == "B3"){
        benchmark_list.clear();
        benchmark_list.push_back("Irnich_BPP");
    } else if (mode == "B4"){
        benchmark_list.clear();
        benchmark_list.push_back("Scholl");
    } else if (mode == "B5"){
        benchmark_list.clear();
        benchmark_list.push_back("Schwerin");
    }

    for (string& benchmark : benchmark_list)
    {
        // Open the list of instances of this benchmark to run
        string infile_list(data_path+benchmark+"_list.txt");
        ifstream f_list(infile_list);
        if (!f_list.is_open())
        {
            string s("Cannot open instance list file " + infile_list);
            throw std::runtime_error(s);
        }
        cout << "Loading instances from " << benchmark << endl;


        // Prepare the output file
        string outfile(output_path + "BPPLIB_" + benchmark + "_dim1.csv");
        ofstream f(outfile, ios_base::trunc);
        if (!f.is_open())
        {
            string s("Cannot write file " + outfile);
            throw std::runtime_error(s);
        }
        cout << "Writing output to file " << outfile << endl;

        // Header line
        string header("instance_name\tLB");
        string time_header;

        for (std::string algo_name : list_centric)
        {
            header.append("\t" + map_rename_algos.at(algo_name));
            time_header.append("\t" + map_rename_algos.at(algo_name) + "_timems");
        }
        for (std::string algo_name : list_WFDm)
        {
            header.append("\t" + map_rename_algos.at(algo_name));
            time_header.append("\t" + map_rename_algos.at(algo_name) + "_timems");
        }
        f << header << time_header << "\n";
        f.flush();

        // For each instance in the file, run
        string line, instance_name, instance_file;
        while(getline(f_list, line))
        {
            if (line.size() > 0)
            {
                istringstream splitStr(line);
                getline(splitStr, instance_name, ' ');
                getline(splitStr, instance_file, '\n');

                const Instance instance(instance_name, data_path + instance_file);

                string row_str = run_for_instance(instance, list_centric, list_WFDm);
                f << instance_name << "\t" << row_str << "\n";
                f.flush();
            }
        }
        f_list.close();
        f.close();
    }
}



int main(int argc, char** argv)
{
    string input_path("/home/mommess/Documents/Vectorpack/experiments_vector_paper/data/1dim/");
    string output_path("/home/mommess/Documents/Vectorpack/experiments_vector_paper/results_data/TEST_");
    //string input_path("/nobackup/scscm/data_vector/1dim/");
    //string output_path("/nobackup/scscm/output_vector/");

    std::string mode;
    if (argc > 1)
    {
        mode = argv[1];
    }

    vector<string> list_centric= {
        "FF",
        "FFD-L1-Unit",
        "BFD-T1-L1-Unit",
        "WFD-T1-L1-Unit",
        "BF-L1-Unit",
        "WF-L1-Unit",

        // "BCS-L2Norm-Unit", // should be identical to FFD
    };
    vector<string> list_WFDm = {
        "WFDm-BS-L1-Unit",
    };
    /*vector<string> list_BIMs = {
        "Pairing-BS-DP3-Unit", // Identical to BFD

        "Pairing-BS-L2Norm-Unit", // Should be like FFD
    };*/

    map<string, string> map_rename_algos = {
        { "FF", "FF" },
        { "FFD-L1-Unit", "FFD" },
        { "BFD-T1-L1-Unit", "BFD" },
        { "WFD-T1-L1-Unit", "WFD" },
        { "BF-L1-Unit", "BF" },
        { "WF-L1-Unit", "WF" },

        //{ "BCS-L2Norm-Unit", "BCS-L2Norm" },

        { "WFDm-BS-L1-Unit", "WFDm" },

        //{ "Pairing-BS-DP3-Unit", "Pairing-DP3" },
        //{ "Pairing-BS-L2Norm-Unit", "Pairing-L2Norm" },
    };

    if (mode.front() == 'B')
    {
        //run_BPPLIB(input_path, output_path, list_centric, list_BIMs, list_WFDm, map_rename_algos, mode);
        run_BPPLIB(input_path, output_path, list_centric, list_WFDm, map_rename_algos, mode);
    }

    cout << "Run successful!" << endl;
    return 0;
}
