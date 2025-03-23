#ifndef S3RAND_H
#define S3RAND_H

#include "../../utility/header/ArrBoolInt.h"
#include <iostream>
#include <list>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Class S3Rand provides the core of an iterative algorithm that generates a
 * state space for solving the subset-sum problem using different strategies for
 * managing live nodes and selecting the eNode.
 */
class S3Rand {
public:
  /**
   * Main function for processing the subset-sum problem using a list of live
   * nodes.
   * @param insieme A vector of integers representing the set.
   * @param s The target sum to be matched.
   * @param liveNodes A list of ArrBoolInt representing the live nodes.
   */
  void risposte(const vector<int> &insieme, int s, list<ArrBoolInt> &liveNodes);

  /**
   * Extracts an eNode according to the implemented policy and returns it.
   * @param insieme A vector of integers representing the set.
   * @param s The target sum.
   * @param liveNodes A list of live nodes.
   * @return An ArrBoolInt representing the eNode.
   */
  ArrBoolInt eNode(const vector<int> &insieme, int s,
                   list<ArrBoolInt> liveNodes);

  /**
   * Estimates the defect cost based on the subset sum.
   * @param insieme A vector of integers representing the set.
   * @param fH The current cost function value.
   * @param s The target sum.
   * @param liveNode The current live node.
   * @return The defect cost.
   */
  int stimaCostoPerDifetto(const vector<int> &insieme, int fH, int s,
                           ArrBoolInt liveNode);

  /**
   * Estimates the excess cost based on the subset sum.
   * @param insieme A vector of integers representing the set.
   * @param fH The current cost function value.
   * @param s The target sum.
   * @param liveNode The current live node.
   * @return The excess cost.
   */
  int stimaCostoPerEccesso(const vector<int> &insieme, int fH, int s,
                           ArrBoolInt liveNode);

  /**
   * Computes the cost function for a given solution.
   * @param insieme A vector of integers representing the set.
   * @param s The target sum.
   * @param liveNodes The list of live nodes.
   * @return The computed cost.
   */
  int fCompostoH(const vector<int> &insieme, int s, ArrBoolInt liveNodes);

  /**
   * Expands the live node list by adding two child nodes.
   * @param node The current eNode.
   * @param liveNodes The list of live nodes.
   * @return The updated list of live nodes.
   */
  list<ArrBoolInt> espande(ArrBoolInt node, list<ArrBoolInt> liveNodes);

  /**
   * Selects an eNode randomly from the list of live nodes.
   * @param insieme A vector of integers representing the set.
   * @param s The target sum.
   * @param liveNodes The list of live nodes.
   * @return The index of the selected eNode.
   */
  int getIndiceENode(const vector<int> &insieme, int s,
                     list<ArrBoolInt> liveNodes);

  /**
   * Checks if the node is complete.
   * @param insieme A vector of integers representing the set.
   * @param s The target sum.
   * @param node The current live node.
   * @return True if the node is complete, otherwise false.
   */
  bool completo(vector<int> insieme, int s, ArrBoolInt node);

  /**
   * Rejects the current live node if certain conditions are met.
   * @param insieme A vector of integers representing the set.
   * @param somma The target sum.
   * @param node The current live node.
   * @param liveNodes The list of live nodes.
   * @return True if the node is rejected, otherwise false.
   */
  bool rifiuta(vector<int> insieme, int somma, ArrBoolInt node,
               list<ArrBoolInt> liveNodes);

  /**
   * Accepts the current live node if it satisfies the target sum condition.
   * @param insieme A vector of integers representing the set.
   * @param somma The target sum.
   * @param node The current live node.
   * @return True if the node is accepted, otherwise false.
   */
  bool accetta(vector<int> insieme, int somma, ArrBoolInt node);

private:
  /**
   * Converts an integer to a string.
   * @param num The integer to be converted.
   * @return The string representation of the integer.
   */
  string intToString(int num);

  /**
   * Converts an eNode to a string.
   * @param insieme A vector of integers representing the set.
   * @param eNode The eNode to be converted.
   * @return The string representation of the eNode.
   */
  string toStringENode(const vector<int> &insieme, ArrBoolInt eNode);

  /**
   * Converts the list of live nodes to a string.
   * @param insieme A vector of integers representing the set.
   * @param liveNodes The list of live nodes.
   * @return The string representation of the live nodes.
   */
  string toStringLiveNodes(const vector<int> &insieme,
                           const list<ArrBoolInt> &liveNodes);
};

#endif // S3RAND_H
