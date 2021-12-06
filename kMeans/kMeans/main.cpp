#include "cluster.hpp"
#include <string>

bool ClusterPoints(Cluster*, Points&, int);

int main() {


	//Set the range
	double maxX = 50, minX = -50;
	double maxY = 50, minY = -50;

	//Get random points
	Points all_points;
	all_points.generate_random_points(80, maxX, minX, maxY, minY);

	// change number of clusters
	const int num_clusters = 6;

	//create clusters 
	Cluster clusters[num_clusters];

	// change radius
	double radius = 30;

	//generate random centroid (seed points) for clusters
	for (int i = 0; i < num_clusters; i++) {
		clusters[i].set_radius(radius);										// set radius of all clusters
		clusters[i].generate_random_centroid(maxX, minX, maxY, minY, i);
	}

	int count = 0;

	bool loc_change = ClusterPoints(clusters, all_points, num_clusters);
	count++;

	while (loc_change) {
		for (int i = 0; i < num_clusters; i++) {
			clusters[i].recalculate_centroid();
		}

		loc_change = ClusterPoints(clusters, all_points, num_clusters);
		count++;
	}

	std::cout << all_points << std::endl;
	for (int i = 0; i < num_clusters; i++) {
		std::cout << "Cluster " << i << '\n';
		std::cout << clusters[i];
	}
	std::cout << "Times run: " << count << '\n'; 
}

	// cycle through all_points and check dist to centroid of all clusters.
	// assign to private member variable members of lowest distance. 
	// re calc cluster centoid
	// end when no point moves.

bool ClusterPoints(Cluster* c, Points& pts, int nc) {
	bool changed_location = false;
	for (int i = 0; i < pts.get_size(); i++) {							// loop through every point
		double shortest_dist = distance(c[0].get_centroid(), pts[i]);	// set shortest dist
		int indx_of_cluster = 0;										// initizalize indx of cluster to put it in. assume cluster 0
		for (int j = 1; j < nc; j++) {									// loop through all clusters besides the first
			double cur_dist = distance(c[j].get_centroid(), pts[i]);	// calculate dist
			if (shortest_dist > cur_dist) {								// if dist is shorter than current shortest dist
				shortest_dist = cur_dist;								// change shortest dist
				indx_of_cluster = j;									// change indx of cluster
			}
		}

		if (shortest_dist <= c[indx_of_cluster].get_radius()) {				// check if the distance is in the radius
			if (pts[i].cluster != indx_of_cluster) {						// check if it changed location
				if (pts[i].cluster != -1) {									// check wasn't a no one
					c[pts[i].cluster].get_members().remove_point(pts[i]);	// remove from old place
				}
				changed_location = true;									// set change of location
				pts[i].cluster = indx_of_cluster;							// set points cluster
			}

			c[indx_of_cluster].get_members().add_point(pts[i]);				// add it
		}
		else {																// else not adding it to current cluster
			if (pts[i].cluster != -1) {
				changed_location = true;
				c[pts[i].cluster].get_members().remove_point(pts[i]);
			}
			pts[i].cluster = -1;
		}
	}

	return changed_location;
}