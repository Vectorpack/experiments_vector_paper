#include <algo_utils.hpp>
#include "algo_lists.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>

using namespace std;
using namespace std::chrono;
using namespace vectorpack;


std::string run_for_instance(const Instance & instance,
                             const vector<string> & list_centric,
                             const vector<string> & list_pairing,
                             const vector<string> & list_WFDm)
{
    int LB1 = LB_BPP(instance);
    int LB2 = LB_clique(instance);
    int LB = std::max(LB1, LB2);

    int hint_bin = LB + 50; // Arbitrarily set
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

    for (const string & algo_name : list_pairing)
    {
        AlgoPairing * algo = createAlgoPairing(algo_name, instance);

        auto start = high_resolution_clock::now();
        sol = algo->solveInstanceMultiBin(LB, UB);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        row_res.append("\t" + to_string(sol));
        row_time.append("\t" + to_string((float)duration.count()));

        delete algo;
    }

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


void run_class(string& input_path, string& outfile,
                   const vector<string> list_centric,
                   const vector<string> list_pairing,
                   const vector<string> list_WFDm,
                   const vector<int> list_d,
                   const vector<int> list_n,
                   const vector<string> list_c,
                   const string full_mode)
{
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
        header.append("\t" + algo_name);
        time_header.append("\t" + algo_name + "_timems");
    }
    for (std::string algo_name : list_pairing)
    {
        header.append("\t" + algo_name);
        time_header.append("\t" + algo_name + "_timems");
    }
    for (std::string algo_name : list_WFDm)
    {
        header.append("\t" + algo_name);
        time_header.append("\t" + algo_name + "_timems");
    }
    f << header << time_header << "\n";
    f.flush();

    for (const string &c : list_c)
    {
        cout << "class " << c << endl;

        string prefix_name;
        if (full_mode == "Triplet")
        {
            prefix_name = "class" + string(1, c[0]);
        }
        else
        {
            prefix_name = c;
        }

        for (int d : list_d)
        {
            for (int n : list_n)
            {
                cout << "Starting n=" << n << " d=" << d << endl;
                for (int i = 0; i < 10; i++)
                {
                    cout << i << " ";

                    string instance_name(prefix_name + "_" + to_string(n) + "_" + to_string(d) + "_" + to_string(i));
                    string infile(input_path + full_mode + "_instances_multidim/"+ c + "/" + instance_name + ".vbp");
                    const Instance instance(instance_name, infile);

                    string row_str = run_for_instance(instance, list_centric,
                                                      list_pairing, list_WFDm);
                    f << instance_name << "\t" << row_str << "\n";
                    f.flush();
                    cout << flush;
                }
                cout << endl;
            }
        }
    }

    f.close();
}




int main(int argc, char** argv)
{

    string input_path("/home/mommess/Documents/Vectorpack/experiments_vector_paper/data/");
    string output_path("/home/mommess/Documents/Vectorpack/experiments_vector_paper/results_data/TEST_");

    string mode;
    string class_name = "";
    if (argc>2)
    {
        mode = argv[1];

        if (mode != "T")
        {
            class_name += "class";
        }
        class_name += argv[2];
    }
    else
    {
        cout << "Usage: " << argv[0] << " <T|P|I> <class number>" << endl;
        return -1;
    }

    cout << "Number of Item-centric and Bin-centric algos: " << list_centric.size() << endl;
    cout << "Number of Pairing algos: " << list_pairing.size() << endl;
    cout << "Number of WFDm/BFDm algos: " << list_WFDm.size() << endl;

    string full_mode;
    vector<int> list_d = {3, 5, 10};
    vector<int> list_n;
    vector<string> list_c;

    if (mode == "T")
    {
        full_mode = "Triplet";
        list_n = {60, 120, 249, 501};

        if (class_name == "all")
        {
            list_c = {"Caprara", "Falkenauer"};
        }
        else
        {
            list_c.push_back(class_name);
        }
    }
    else if (mode == "P")
    {
        full_mode = "Panigrahy";
        list_n = {20, 40, 60, 120, 250, 500};

        if (class_name == "classall")
        {
            list_c = {"class1", "class2", "class3",
                      "class4", "class5", "class6",
                      "class7", "class8", "class9"};
        }
        else
        {
            list_c.push_back(class_name);
        }
    }
    else if (mode == "N")
    {
        full_mode = "New";
        list_n = {20, 40, 60, 120, 250, 500};

        if (class_name == "classall")
        {
            list_c = {"class1", "class2", "class3",
                      "class4", "class5", "class6"};
        }
        else
        {
            list_c.push_back(class_name);
        }
    }

    string outfile;
    if (class_name == "classall" or class_name == "all")
    {
        outfile = output_path + full_mode + "_multidim.csv";
    }
    else
    {
        outfile = output_path + full_mode + "_multidim_" + class_name + ".csv";
    }

    run_class(input_path, outfile,
              list_centric,
              list_pairing, list_WFDm,
              list_d, list_n, list_c,
              full_mode);

    cout << "Run successful!" << endl;
    return 0;
}


