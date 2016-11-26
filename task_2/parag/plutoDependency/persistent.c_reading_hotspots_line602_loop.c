[pluto] compute_deps (isl)
nvar = 2, npar = 1
Parameters: board_size 
S1 "values[19 + 2 + m *(19 + 1) + n] = 0.0;"
ndims: 2; orig_depth: 2
Index set
Set #1
[3 dims; 5 constraints]
m >= 0
-m+board-1 >= 0
board-1 >= 0
n >= 0
-n+board-1 >= 0

T(S1): (0, m, 0, n, 0)
loop types (loop, loop, loop, loop, loop)

No Read accesses
Write accesses
values[20m+n+21]
Original loop: 0 -> yes
Original loop: 1 -> yes

--- Dep 1 from S1 to S1; satisfied: 0, sat level: -1; Type: WAW
on variable: values
Dependence polyhedron
Set #1
[5 dims; 11 constraints]
-20m-n+20m'+n' = 0
m >= 0
-m+board-1 >= 0
board-1 >= 0
n >= 0
-n+board-1 >= 0
m' >= 0
-m'+board-1 >= 0
-20m-n+20m'+board-1 >= 0
20m+n-20m' >= 0
-m+m'-1 >= 0


T(S1): (0, m, 0, n, 0)
loop types (loop, loop, loop, loop, loop)

[pluto] Number of statements: 1
[pluto] Total number of loops: 2
[pluto] Number of deps: 1
[pluto] Maximum domain dimensionality: 2
[pluto] Number of parameters: 1
[pluto] ddg_compute_scc
[pluto] dfs_for_scc: SCC 0: Stmt ids:  0


	SCC 0: size: 1: max stmt dim: 2
[pluto] parameter context from domains
Set #1
[1 dims; 1 constraints]
c_i-1 >= 0

[pluto] find_permutable_hyperplanes: max solution(s): 2; band depth: 0
[pluto] compute permutability constraints: Dep 1
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_x) from 19 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_w) from 18 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_l) from 17 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_u) from 15 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_t) from 14 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_s) from 13 constraints
[farkas_lemma_affine] eliminating multiplier 6 (c_r) from 11 constraints
[farkas_lemma_affine] eliminating multiplier 7 (c_p) from 10 constraints
[farkas_lemma_affine] eliminating multiplier 8 (c_o) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 9 (c_n) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 10 (c_m) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 11 (c_m) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 12 (c_l) from 4 constraints
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_{) from 20 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_z) from 19 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_n) from 18 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_x) from 16 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_w) from 15 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_v) from 14 constraints
[farkas_lemma_affine] eliminating multiplier 6 (c_u) from 13 constraints
[farkas_lemma_affine] eliminating multiplier 7 (c_t) from 12 constraints
[farkas_lemma_affine] eliminating multiplier 8 (c_r) from 11 constraints
[farkas_lemma_affine] eliminating multiplier 9 (c_q) from 10 constraints
[farkas_lemma_affine] eliminating multiplier 10 (c_p) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 11 (c_o) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 12 (c_o) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 13 (c_n) from 7 constraints
	For dep: 1; num_constraints: 9
	After dep: 1; num_constraints: 9
	After all dependences: num constraints: 9, num variables: 5
Adding lower bound 0 for transformation coefficients
Adding lower bound 0 for transformation coefficients
Adding lower bound 0 for transformation coefficients
[pluto] get_linear_ind_constraints
[pluto] get_stmt_ortho constraints S1
Ortho constraints for S1; 2 disjuncts
Added ortho constraints for S1
linear independence constraints
[5 dims; 1 constraints]
            +c_k +c_l       -1 >= 0

[pluto] (Band 1) Solving for hyperplane #1
[pluto] pluto_prog_constraints_lexmin (5 variables, 16 constraints)
[pluto] pluto_constraints_lexmin_isl (5 variables, 16 constraints)
[pluto] find_permutable_hyperplanes: found a hyperplane
h(S1) = 20m+n
[pluto] get_linear_ind_constraints
[pluto] get_stmt_ortho constraints S1
Ortho constraints for S1; 1 disjuncts
Added ortho constraints for S1
linear independence constraints
[5 dims; 1 constraints]
            +c_k -20c_l       -1 >= 0

[pluto] (Band 1) Solving for hyperplane #2
[pluto] pluto_prog_constraints_lexmin (5 variables, 16 constraints)
[pluto] pluto_constraints_lexmin_isl (5 variables, 16 constraints)
[pluto] find_permutable_hyperplanes: found a hyperplane
h(S1) = m
[pluto] pluto_auto_transform: band level 0; 2 hyperplane(s) found
T(S1): (20m+n, m)
loop types (loop, loop)

[pluto] dep_satisfaction_update (level 0)
	 0 dep(s) satisfied
[pluto] updating DDG
[pluto] dep_satisfaction_update (level 1)
[pluto] dep_satisfaction_update: dep 1 satisfied
	 1 dep(s) satisfied
[pluto] updating DDG
[pluto] pluto_auto_transform: successful, done
[pluto] pluto_detect_transformation_properties
[pluto] pluto_compute_dep_satisfaction
[pluto] pluto_dep_satisfaction_reset
[pluto] dep_satisfaction_update (level 0)
	 0 dep(s) satisfied
[pluto] dep_satisfaction_update (level 1)
[pluto] dep_satisfaction_update: dep 1 satisfied
	 1 dep(s) satisfied
[pluto] Affine transformations [<iter coeff's> <param> <const>]

T(S1): (20m+n, m)
loop types (loop, loop)

t1 --> parallel loop   (band 0)no-ujam
t2 --> fwd_dep  loop   (band 0)no-ujam

[pluto-intra-tile-opt] Score for loop 0: 4
t2 {loop with stmts: S1, }
[pluto-intra-tile-opt] Score for loop 1: -16
t1 {loop with stmts: S1, }
[pluto] generating Cloog file...
[pluto] using Cloog -f/-l options: 1 2
[pluto] cloog_input_read
[pluto] cloog_clast_create
[pluto_mark_vector] parallel loops
t1 {loop with stmts: S1, }
[Pluto] Output written to persistent.c_reading_hotspots_line602_loop.pluto.c
