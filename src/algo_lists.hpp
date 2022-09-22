#include <vector>
#include <string>

using namespace std;

// list_algos for ALL item-centric variants
vector<string> list_centric = {
    "FF",
    // FFD static
    "FFD-L1-Unit", "FFD-L1-Avg", "FFD-L1-Expo", "FFD-L1-ReciprocAvg",
    "FFD-Linf-Unit", "FFD-Linf-Avg", "FFD-Linf-Expo", "FFD-Linf-ReciprocAvg",
    "FFD-L2-Unit", "FFD-L2-Avg", "FFD-L2-Expo", "FFD-L2-ReciprocAvg",

    // FFD dynamic item weights
    "FFD-L1-Avg-Dyn", "FFD-L1-Expo-Dyn", "FFD-L1-ReciprocAvg-Dyn",
    "FFD-Linf-Avg-Dyn", "FFD-Linf-Expo-Dyn", "FFD-Linf-ReciprocAvg-Dyn",
    "FFD-L2-Avg-Dyn", "FFD-L2-Expo-Dyn", "FFD-L2-ReciprocAvg-Dyn",

    // FFD with ResidualRatio (similar to dynamic div avg) and UtilRatio dynamic weights
    "FFD-L1-UtilRatio",
    "FFD-Linf-UtilRatio",
    "FFD-L2-UtilRatio",


    // BFD T1 static
    "BFD-T1-L1-Unit", "BFD-T1-L1-Avg", "BFD-T1-L1-Expo", "BFD-T1-L1-ReciprocAvg",
    "BFD-T1-Linf-Unit", "BFD-T1-Linf-Avg", "BFD-T1-Linf-Expo", "BFD-T1-Linf-ReciprocAvg",
    "BFD-T1-L2-Unit", "BFD-T1-L2-Avg", "BFD-T1-L2-Expo", "BFD-T1-L2-ReciprocAvg",
    "BFD-T1-L2Load-Unit", "BFD-T1-L2Load-Avg", "BFD-T1-L2Load-Expo", "BFD-T1-L2Load-ReciprocAvg",

    // BFD T1 dynamic item weights
    "BFD-T1-L1-Avg-Dyn", "BFD-T1-L1-Expo-Dyn", "BFD-T1-L1-ReciprocAvg-Dyn",
    "BFD-T1-Linf-Avg-Dyn", "BFD-T1-Linf-Expo-Dyn", "BFD-T1-Linf-ReciprocAvg-Dyn",
    "BFD-T1-L2-Avg-Dyn", "BFD-T1-L2-Expo-Dyn", "BFD-T1-L2-ReciprocAvg-Dyn",
    "BFD-T1-L2Load-Avg-Dyn", "BFD-T1-L2Load-Expo-Dyn", "BFD-T1-L2Load-ReciprocAvg-Dyn",

    // BFD with ResidualRatio and UtilRatio dynamic weights
    "BFD-T1-L1-UtilRatio",
    "BFD-T1-Linf-UtilRatio",
    "BFD-T1-L2-UtilRatio",
    "BFD-T1-L2Load-UtilRatio",


    // BFD T2
    "BFD-T2-L1-Avg", "BFD-T2-L1-Expo", "BFD-T2-L1-ReciprocAvg",
    "BFD-T2-Linf-Avg", "BFD-T2-Linf-Expo", "BFD-T2-Linf-ReciprocAvg",
    "BFD-T2-L2-Avg", "BFD-T2-L2-Expo", "BFD-T2-L2-ReciprocAvg",
    "BFD-T2-L2Load-Avg", "BFD-T2-L2Load-Expo", "BFD-T2-L2Load-ReciprocAvg",

    // BFD T2 dynamic item weights
    "BFD-T2-L1-Avg-Dyn", "BFD-T2-L1-Expo-Dyn", "BFD-T2-L1-ReciprocAvg-Dyn",
    "BFD-T2-Linf-Avg-Dyn", "BFD-T2-Linf-Expo-Dyn", "BFD-T2-Linf-ReciprocAvg-Dyn",
    "BFD-T2-L2-Avg-Dyn", "BFD-T2-L2-Expo-Dyn", "BFD-T2-L2-ReciprocAvg-Dyn",
    "BFD-T2-L2Load-Avg-Dyn", "BFD-T2-L2Load-Expo-Dyn", "BFD-T2-L2Load-ReciprocAvg-Dyn",


    // BFD T3 Unit + ReciprocAvg
    "BFD-T3-L1-Unit-ReciprocAvg",
    "BFD-T3-Linf-Unit-ReciprocAvg",
    "BFD-T3-L2-Unit-ReciprocAvg",
    "BFD-T3-L2Load-Unit-ReciprocAvg",

    // BFD T3 Avg + ReciprocAvg
    "BFD-T3-L1-Avg-ReciprocAvg",
    "BFD-T3-Linf-Avg-ReciprocAvg",
    "BFD-T3-L2-Avg-ReciprocAvg",
    "BFD-T3-L2Load-Avg-ReciprocAvg",

    "BFD-T3-L1-Avg-ReciprocAvg-Dyn",
    "BFD-T3-Linf-Avg-ReciprocAvg-Dyn",
    "BFD-T3-L2-Avg-ReciprocAvg-Dyn",
    "BFD-T3-L2Load-Avg-ReciprocAvg-Dyn",

    // BFD T3 Avg + Unit
    "BFD-T3-L1-Avg-Unit",
    "BFD-T3-Linf-Avg-Unit",
    "BFD-T3-L2-Avg-Unit",
    "BFD-T3-L2Load-Avg-Unit",

    "BFD-T3-L1-Avg-Unit-Dyn",
    "BFD-T3-Linf-Avg-Unit-Dyn",
    "BFD-T3-L2-Avg-Unit-Dyn",
    "BFD-T3-L2Load-Avg-Unit-Dyn",


    // BF only
    "BF-L1-Unit", "BF-L1-Avg", "BF-L1-Expo",
    "BF-L1-UtilRatio",
    "BF-Linf-Unit", "BF-Linf-Avg", "BF-Linf-Expo",
    "BF-Linf-UtilRatio",
    "BF-L2-Unit", "BF-L2-Avg", "BF-L2-Expo",
    "BF-L2-UtilRatio",
    "BF-L2Load-Unit", "BF-L2Load-Avg", "BF-L2Load-Expo",
    "BF-L2Load-UtilRatio",


    // WFD T1 static
    "WFD-T1-L1-Unit", "WFD-T1-L1-Avg", "WFD-T1-L1-Expo", "WFD-T1-L1-ReciprocAvg",
    "WFD-T1-Linf-Unit", "WFD-T1-Linf-Avg", "WFD-T1-Linf-Expo", "WFD-T1-Linf-ReciprocAvg",
    "WFD-T1-L2-Unit", "WFD-T1-L2-Avg", "WFD-T1-L2-Expo", "WFD-T1-L2-ReciprocAvg",
    "WFD-T1-L2Load-Unit", "WFD-T1-L2Load-Avg", "WFD-T1-L2Load-Expo", "WFD-T1-L2Load-ReciprocAvg",

    // WFD T1 dynamic item weights
    "WFD-T1-L1-Avg-Dyn", "WFD-T1-L1-Expo-Dyn", "WFD-T1-L1-ReciprocAvg-Dyn",
    "WFD-T1-Linf-Avg-Dyn", "WFD-T1-Linf-Expo-Dyn", "WFD-T1-Linf-ReciprocAvg-Dyn",
    "WFD-T1-L2-Avg-Dyn", "WFD-T1-L2-Expo-Dyn", "WFD-T1-L2-ReciprocAvg-Dyn",
    "WFD-T1-L2Load-Avg-Dyn", "WFD-T1-L2Load-Expo-Dyn", "WFD-T1-L2Load-ReciprocAvg-Dyn",

    // WFD with ResidualRatio and UtilRatio dynamic weights
    "WFD-T1-L1-UtilRatio",
    "WFD-T1-Linf-UtilRatio",
    "WFD-T1-L2-UtilRatio",
    "WFD-T1-L2Load-UtilRatio",


    // WFD T2
    "WFD-T2-L1-Avg", "WFD-T2-L1-Expo", "WFD-T2-L1-ReciprocAvg",
    "WFD-T2-Linf-Avg", "WFD-T2-Linf-Expo", "WFD-T2-Linf-ReciprocAvg",
    "WFD-T2-L2-Avg", "WFD-T2-L2-Expo", "WFD-T2-L2-ReciprocAvg",
    "WFD-T2-L2Load-Avg", "WFD-T2-L2Load-Expo", "WFD-T2-L2Load-ReciprocAvg",

    // WFD T2 dynamic item weights
    "WFD-T2-L1-Avg-Dyn", "WFD-T2-L1-Expo-Dyn", "WFD-T2-L1-ReciprocAvg-Dyn",
    "WFD-T2-Linf-Avg-Dyn", "WFD-T2-Linf-Expo-Dyn", "WFD-T2-Linf-ReciprocAvg-Dyn",
    "WFD-T2-L2-Avg-Dyn", "WFD-T2-L2-Expo-Dyn", "WFD-T2-L2-ReciprocAvg-Dyn",
    "WFD-T2-L2Load-Avg-Dyn", "WFD-T2-L2Load-Expo-Dyn", "WFD-T2-L2Load-ReciprocAvg-Dyn",

    // WF only
    "WF-L1-Unit", "WF-L1-Avg", "WF-L1-Expo",
    "WF-L1-UtilRatio",
    "WF-Linf-Unit", "WF-Linf-Avg", "WF-Linf-Expo",
    "WF-Linf-UtilRatio",
    "WF-L2-Unit", "WF-L2-Avg", "WF-L2-Expo",
    "WF-L2-UtilRatio",
    "WF-L2Load-Unit", "WF-L2Load-Avg", "WF-L2Load-Expo",
    "WF-L2Load-UtilRatio",

    // WFD T3 Unit + ReciprocAvg
    "WFD-T3-L1-Unit-ReciprocAvg",
    "WFD-T3-Linf-Unit-ReciprocAvg",
    "WFD-T3-L2-Unit-ReciprocAvg",
    "WFD-T3-L2Load-Unit-ReciprocAvg",

    // WFD T3 Avg + ReciprocAvg
    "WFD-T3-L1-Avg-ReciprocAvg",
    "WFD-T3-Linf-Avg-ReciprocAvg",
    "WFD-T3-L2-Avg-ReciprocAvg",
    "WFD-T3-L2Load-Avg-ReciprocAvg",

    "WFD-T3-L1-Avg-ReciprocAvg-Dyn",
    "WFD-T3-Linf-Avg-ReciprocAvg-Dyn",
    "WFD-T3-L2-Avg-ReciprocAvg-Dyn",
    "WFD-T3-L2Load-Avg-ReciprocAvg-Dyn",

    // WFD T3 Avg + Unit
    "WFD-T3-L1-Avg-Unit",
    "WFD-T3-Linf-Avg-Unit",
    "WFD-T3-L2-Avg-Unit",
    "WFD-T3-L2Load-Avg-Unit",

    "WFD-T3-L1-Avg-Unit-Dyn",
    "WFD-T3-Linf-Avg-Unit-Dyn",
    "WFD-T3-L2-Avg-Unit-Dyn",
    "WFD-T3-L2Load-Avg-Unit-Dyn",

// list_algos for ALL bin-centric variants
    //BCS stands for Bin-Centric with Score
    // BCS DP1 with static weights, dynamic weights, ratio weights
    "BCS-DP1-Unit", "BCS-DP1-Avg", "BCS-DP1-Expo", "BCS-DP1-ReciprocAvg",
    "BCS-DP1-Avg-Dyn", "BCS-DP1-Expo-Dyn", "BCS-DP1-ReciprocAvg-Dyn",
    "BCS-DP1-Avg-Bin", "BCS-DP1-Expo-Bin", "BCS-DP1-ReciprocAvg-Bin",
    "BCS-DP1-UtilRatio",

    // BCS DP2 with static weights, dynamic weights, ratio weights
    "BCS-DP2-Unit", "BCS-DP2-Avg", "BCS-DP2-Expo", "BCS-DP2-ReciprocAvg",
    "BCS-DP2-Avg-Dyn", "BCS-DP2-Expo-Dyn", "BCS-DP2-ReciprocAvg-Dyn",
    "BCS-DP2-Avg-Bin", "BCS-DP2-Expo-Bin", "BCS-DP2-ReciprocAvg-Bin",
    "BCS-DP2-UtilRatio",

    // BCS NormDP with static weights, dynamic weights, ratio weights
    "BCS-NormDP-Unit", "BCS-NormDP-Avg", "BCS-NormDP-Expo", "BCS-NormDP-ReciprocAvg",
    "BCS-NormDP-Avg-Dyn", "BCS-NormDP-Expo-Dyn", "BCS-NormDP-ReciprocAvg-Dyn",
    "BCS-NormDP-Avg-Bin", "BCS-NormDP-Expo-Bin", "BCS-NormDP-ReciprocAvg-Bin",
    "BCS-NormDP-UtilRatio",

    // BCS L2Norm with static weights, dynamic weights, ratio weights
    "BCS-L2Norm-Unit", "BCS-L2Norm-Avg", "BCS-L2Norm-Expo", "BCS-L2Norm-ReciprocAvg",
    "BCS-L2Norm-Avg-Dyn", "BCS-L2Norm-Expo-Dyn", "BCS-L2Norm-ReciprocAvg-Dyn",
    "BCS-L2Norm-Avg-Bin", "BCS-L2Norm-Expo-Bin", "BCS-L2Norm-ReciprocAvg-Bin",
    "BCS-L2Norm-UtilRatio",

    // BCS TFSum with static weights, dynamic weights, ratio weights
    "BCS-TFSum-Unit", "BCS-TFSum-Avg", "BCS-TFSum-Expo", "BCS-TFSum-ReciprocAvg",
    "BCS-TFSum-Avg-Dyn", "BCS-TFSum-Expo-Dyn", "BCS-TFSum-ReciprocAvg-Dyn",
    "BCS-TFSum-Avg-Bin", "BCS-TFSum-Expo-Bin", "BCS-TFSum-ReciprocAvg-Bin",
    "BCS-TFSum-UtilRatio",

    // BCS TFMin with static weights, dynamic weights, ratio weights
    "BCS-TFMin-Unit", "BCS-TFMin-Avg", "BCS-TFMin-Expo", "BCS-TFMin-ReciprocAvg",
    "BCS-TFMin-Avg-Dyn", "BCS-TFMin-Expo-Dyn", "BCS-TFMin-ReciprocAvg-Dyn",
    "BCS-TFMin-Avg-Bin", "BCS-TFMin-Expo-Bin", "BCS-TFMin-ReciprocAvg-Bin",
    "BCS-TFMin-UtilRatio",
};


// list_algos for ALL bin-item matching variants
vector<string> list_pairing = {
// With Relaxed Binary Search method
    // BIM DP1 with static weights, dynamic weights, ratio weights
    "Pairing-BS-DP1-Unit", "Pairing-BS-DP1-Avg", "Pairing-BS-DP1-Expo", "Pairing-BS-DP1-ReciprocAvg",
    "Pairing-BS-DP1-Avg-Dyn", "Pairing-BS-DP1-Expo-Dyn", "Pairing-BS-DP1-ReciprocAvg-Dyn",
    "Pairing-BS-DP1-Avg-Bin", "Pairing-BS-DP1-Expo-Bin", "Pairing-BS-DP1-ReciprocAvg-Bin",
    "Pairing-BS-DP1-UtilRatio",

    // BIM DP2 with static weights, dynamic weights, ratio weights
    "Pairing-BS-DP2-Unit", "Pairing-BS-DP2-Avg", "Pairing-BS-DP2-Expo", "Pairing-BS-DP2-ReciprocAvg",
    "Pairing-BS-DP2-Avg-Dyn", "Pairing-BS-DP2-Expo-Dyn", "Pairing-BS-DP2-ReciprocAvg-Dyn",
    "Pairing-BS-DP2-Avg-Bin", "Pairing-BS-DP2-Expo-Bin", "Pairing-BS-DP2-ReciprocAvg-Bin",
    "Pairing-BS-DP2-UtilRatio",

    // BIM DP3 with static weights, dynamic weights, ratio weights
    "Pairing-BS-DP3-Unit", "Pairing-BS-DP3-Avg", "Pairing-BS-DP3-Expo", "Pairing-BS-DP3-ReciprocAvg",
    "Pairing-BS-DP3-Avg-Dyn", "Pairing-BS-DP3-Expo-Dyn", "Pairing-BS-DP3-ReciprocAvg-Dyn",
    "Pairing-BS-DP3-Avg-Bin", "Pairing-BS-DP3-Expo-Bin", "Pairing-BS-DP3-ReciprocAvg-Bin",
    "Pairing-BS-DP3-UtilRatio",

    // BIM NormDP with static weights, dynamic weights, ratio weights
    "Pairing-BS-NormDP-Unit", "Pairing-BS-NormDP-Avg", "Pairing-BS-NormDP-Expo", "Pairing-BS-NormDP-ReciprocAvg",
    "Pairing-BS-NormDP-Avg-Dyn", "Pairing-BS-NormDP-Expo-Dyn", "Pairing-BS-NormDP-ReciprocAvg-Dyn",
    "Pairing-BS-NormDP-Avg-Bin", "Pairing-BS-NormDP-Expo-Bin", "Pairing-BS-NormDP-ReciprocAvg-Bin",
    "Pairing-BS-NormDP-UtilRatio",
};


// list_algos for ALL LPT matching variants
vector<string> list_WFDm = {
// With Relaxed Binary Search method
    // LPT static
    "WFDm-BS-Linf-Unit", "WFDm-BS-Linf-Avg", "WFDm-BS-Linf-Expo", "WFDm-BS-Linf-ReciprocAvg",
    "WFDm-BS-L1-Unit", "WFDm-BS-L1-Avg", "WFDm-BS-L1-Expo", "WFDm-BS-L1-ReciprocAvg",
    "WFDm-BS-L2-Unit", "WFDm-BS-L2-Avg", "WFDm-BS-L2-Expo", "WFDm-BS-L2-ReciprocAvg",

    // LPT dynamic item weights
    "WFDm-BS-Linf-Avg-Dyn", "WFDm-BS-Linf-Expo-Dyn", "WFDm-BS-Linf-ReciprocAvg-Dyn",
    "WFDm-BS-L1-Avg-Dyn", "WFDm-BS-L1-Expo-Dyn", "WFDm-BS-L1-ReciprocAvg-Dyn",
    "WFDm-BS-L2-Avg-Dyn", "WFDm-BS-L2-Expo-Dyn", "WFDm-BS-L2-ReciprocAvg-Dyn",

    // LPT with ResidualRatio and UtilRatio dynamic weights
    "WFDm-BS-Linf-UtilRatio",
    "WFDm-BS-L1-UtilRatio",
    "WFDm-BS-L2-UtilRatio",

    // BFD with SumSqLoad measure
    "BFDm-BS-L2Load-Unit", "BFDm-BS-L2Load-Avg", "BFDm-BS-L2Load-Expo", "BFDm-BS-L2Load-ReciprocAvg",
    "BFDm-BS-L2Load-Avg-Dyn", "BFDm-BS-L2Load-Expo-Dyn", "BFDm-BS-L2Load-ReciprocAvg-Dyn",
    "BFDm-BS-L2Load-UtilRatio",
};
