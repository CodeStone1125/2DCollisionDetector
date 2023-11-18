#ifndef QUAD_HPP
#define QUAD_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

class Model;

class Quad {
public:
    // Constructor
    Quad(Model& model, std::tuple<int, int, int, int> box, int depth);
    // Member functions
    bool is_leaf() const;
    double compute_area();
    std::vector<Quad> split();
    std::vector<Quad> get_leaf_nodes(int max_depth) const;

// private... maybe... later...
    // Member variables
    Model* m_model;  // Use a pointer to the Model class
    std::tuple<int, int, int, int> m_box;
    bool m_leaf;
    std::vector<int> hist;
    int m_depth;
    std::tuple<int, int, int> m_color;
    double m_error;
    
    double m_area;
    std::vector<Quad> children;

    // Quad Quad::getLastElement() const {

    // return /* 最後一個元素 */;
    // }
};

// For std::priority_queue compare fountion
struct CompareQuad {
    bool operator()(const std::tuple<int, double, Quad>& a, const std::tuple<int, double, Quad>& b) const {
        // compare with 2nd element
        return std::get<1>(a) > std::get<1>(b);
    }
};

class Model {
public:
    Model(const std::string& path);
    std::vector<Quad> getQuads() const;
    double averageError() const;
    void push(Quad& quad);
    Quad pop();
    void split();
    void render(const std::string& filename, int max_depth);
// private... maybe... later...
    cv::Mat im;
    int width;
    int height;
    mutable std::vector<Quad> quads_vector;
    std::priority_queue<std::tuple<int, double, Quad>, std::vector<std::tuple<int, double, Quad>>, CompareQuad> heap;
    Quad* root;  // Use a pointer to the Quad class
    double error_sum;

    // Helper function to convert priority_queue to vector
    std::vector<Quad> convertPriorityQueueToVector(const std::priority_queue<std::tuple<int, double, Quad>, std::vector<std::tuple<int, double, Quad>>, CompareQuad>& pq) const {
        std::vector<Quad> vec;
        std::priority_queue<std::tuple<int, double, Quad>, std::vector<std::tuple<int, double, Quad>>, CompareQuad> temp = pq;  // Make a copy of the original priority_queue

        while (!temp.empty()) {
            vec.push_back(std::get<2>(temp.top()));  // Extract the Quad from the tuple and push it into the vector
            temp.pop();  // Remove the top element
        }

        return vec;
    }
};

#endif // QUAD_HPP
