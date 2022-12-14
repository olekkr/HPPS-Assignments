#include "kdtree.h"
#include "sort.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

// a single node in the kd-tree
struct node {
    int mid_point; // im assuming this is the index of median???
    // dimension on which it is split
    int axis;
    // child nodes, null if no node
    struct node *left;
    struct node *right;
};

struct kdtree {
  int d;
  const double* points;
  struct node* root;
};


// assumes points is sorted 
struct node* kdtree_create_node(int dimensions, int d, const double* points, int n){
    printf("%d %d %d", dimensions, d, n);
    struct node* node = malloc(sizeof(struct node));
    int median_idx = n/2;
    node->mid_point = points[median_idx];
    node->axis = d;

    node->left = NULL;
    node->right = NULL;
    if (n == 0){return NULL;}
    if (n > 1){
        node->left = kdtree_create_node(dimensions, (d+1)%dimensions, points, median_idx);
    }
    if (n > 2){
        node->right = kdtree_create_node(dimensions, (d+1)%dimensions, points+sizeof(double)*median_idx, n-median_idx);
    }
    return node;
}

struct kdtree *kdtree_create(int d, int n, const double *points) {
  struct kdtree *tree = malloc(sizeof(struct kdtree));
  tree->d = d;
  tree->points = points;

  int *indexes = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    indexes[i] = i;
  }
    
  tree->root = kdtree_create_node(d, 0, points, n);

  free(indexes);

  return tree;
}

void kdtree_free_node(struct node *node) {
  assert(0);
}

void kdtree_free(struct kdtree *tree) {
  kdtree_free_node(tree->root);
  free(tree);
}

void kdtree_knn_node(const struct kdtree *tree, int k, const double* query,
                     int *closest, double *radius,
                     const struct node *node) {
  assert(0);
}

int* kdtree_knn(const struct kdtree *tree, int k, const double* query) {
  int* closest = malloc(k * sizeof(int));
  double radius = INFINITY;

  for (int i = 0; i < k; i++) {
    closest[i] = -1;
  }

  kdtree_knn_node(tree, k, query, closest, &radius, tree->root);

  return closest;
}

void kdtree_svg_node(double scale, FILE *f, const struct kdtree *tree,
                     double x1, double y1, double x2, double y2,
                     const struct node *node) {
  if (node == NULL) {
    return;
  }

  double coord = tree->points[node->mid_point*2+node->axis];
  if (node->axis == 0) {
    // Split the X axis, so vertical line.
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
            coord*scale, y1*scale, coord*scale, y2*scale);
    kdtree_svg_node(scale, f, tree,
                    x1, y1, coord, y2,
                    node->left);
    kdtree_svg_node(scale, f, tree,
                    coord, y1, x2, y2,
                    node->right);
  } else {
    // Split the Y axis, so horizontal line.
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
            x1*scale, coord*scale, x2*scale, coord*scale);
    kdtree_svg_node(scale, f, tree,
                    x1, y1, x2, coord,
                    node->left);
    kdtree_svg_node(scale, f, tree,
                    x1, coord, x2, y2,
                    node->right);
  }
}

void kdtree_svg(double scale, FILE* f, const struct kdtree *tree) {
  assert(tree->d == 2);
  kdtree_svg_node(scale, f, tree, 0, 0, 1, 1, tree->root);
}
