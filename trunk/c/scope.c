
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bingham.h"
#include "bingham/util.h"
#include "bingham/olf.h"



void load_params(scope_params_t *params, char *param_file)
{
  FILE *f = fopen(param_file, "r");
  if (f == NULL) {
    fprintf(stderr, "Error loading param file: %s\n", param_file);
    return;
  }

  char sbuf[1024];

  int cnt = 0;
  while (!feof(f)) {
    char *s = sbuf;
    if (fgets(s, 1024, f)) {
      cnt++;
      if (!wordcmp(s, "num_samples", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%d", &params->num_samples);
      }
      else if (!wordcmp(s, "num_samples_init", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%d", &params->num_samples_init);
      }
      else if (!wordcmp(s, "num_correspondences", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%d", &params->num_correspondences);
      }
      else if (!wordcmp(s, "knn", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%d", &params->knn);
      }
      else if (!wordcmp(s, "num_validation_points", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%d", &params->num_validation_points);
      }
      else if (!wordcmp(s, "sift_dthresh", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->sift_dthresh);
      }
      else if (!wordcmp(s, "xyz_weight", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->xyz_weight);
      }
      else if (!wordcmp(s, "normal_weight", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->normal_weight);
      }
      else if (!wordcmp(s, "surfdist_weight", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->surfdist_weight);
      }
      else if (!wordcmp(s, "surfwidth_weight", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->surfwidth_weight);
      }
      else if (!wordcmp(s, "surfdist_thresh", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->surfdist_thresh);
      }
      else if (!wordcmp(s, "surfwidth_thresh", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->surfwidth_thresh);
      }
      else if (!wordcmp(s, "fsurf_sigma", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->fsurf_sigma);
      }
      else if (!wordcmp(s, "L_weight", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->L_weight);
      }
      else if (!wordcmp(s, "range_sigma", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->range_sigma);
      }
      else if (!wordcmp(s, "f_sigma", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->f_sigma);
      }
      else if (!wordcmp(s, "lab_sigma", " \t\n")) {
	s = sword(s, " \t", 1);
	sscanf(s, "%lf", &params->lab_sigma);
      }

      else {
	fprintf(stderr, "Error: bad parameter ''%s'' at line %d of %s\n", s, cnt, param_file);
	exit(1);
      }
    }
  }
}


int main(int argc, char *argv[])
{
  if (argc < 8) {
    printf("usage: %s <pcd_obs> <pcd_obs_fg> <pcd_obs_sift> <pcd_model> <pcd_model_sift> <param_file> <samples_output>\n", argv[0]);
    return 1;
  }

  olf_obs_t obs;
  obs.range_image = pcd_to_range_image(load_pcd(argv[1]), 0, M_PI/1000.0);
  obs.fg_pcd = load_pcd(argv[2]);
  obs.sift_pcd = load_pcd(argv[3]);

  olf_model_t model;
  model.obj_pcd = load_pcd(argv[4]);
  model.sift_pcd = load_pcd(argv[5]);

  scope_params_t params;
  load_params(&params, argv[6]);

  FILE *f = fopen(argv[7], "w");
  if (f == NULL) {
    printf("Can't open %s for writing\n", argv[2]);
    return 1;
  }

  olf_pose_samples_t *poses = scope(&model, &obs, &params);

  // write pose samples to file
  double **X = poses->X;
  double **Q = poses->Q;
  double *W = poses->W;
  int n = poses->n;
  /*
  for (n = 1; n < poses->n; n++)
    if (W[n] < .01 * W[0])
      break;
  mult(W, W, 1/sum(W,n), n);
  */

  fprintf(f, "X = [");
  int i;
  for (i = 0; i < n; i++)
    fprintf(f, "%f, %f, %f;  ", X[i][0], X[i][1], X[i][2]);
  fprintf(f, "];\n");

  fprintf(f, "Q = [");
  for (i = 0; i < n; i++)
    fprintf(f, "%f, %f, %f, %f;  ", Q[i][0], Q[i][1], Q[i][2], Q[i][3]);
  fprintf(f, "];\n");

  fprintf(f, "W = [");
  for (i = 0; i < n; i++)
    fprintf(f, "%f ", W[i]);
  fprintf(f, "];\n");

  fclose(f);

  return 0;
}
