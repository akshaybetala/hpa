[pluto] compute_deps (isl)
nvar = 1, npar = 0
Parameters: 
S1 "sum_of_weights += table[i];"
ndims: 1; orig_depth: 1
Index set
Set #1
[1 dims; 2 constraints]
i >= 0
-i+7 >= 0

T(S1): (0, i, 0)
loop types (loop, loop, loop)

Read accesses
sum_of_weights[0]
table[i]
Write accesses
sum_of_weights[0]
Original loop: 0 -> yes

--- Dep 1 from S1 to S1; satisfied: 0, sat level: -1; Type: RAW
on variable: sum_of_weights
Dependence polyhedron
Set #1
[2 dims; 5 constraints]
i >= 0
-i+7 >= 0
i' >= 0
-i'+7 >= 0
-i+i'-1 >= 0


--- Dep 2 from S1 to S1; satisfied: 0, sat level: -1; Type: WAR
on variable: sum_of_weights
Dependence polyhedron
Set #1
[2 dims; 5 constraints]
i >= 0
-i+7 >= 0
i' >= 0
-i'+7 >= 0
-i+i'-1 >= 0


--- Dep 3 from S1 to S1; satisfied: 0, sat level: -1; Type: WAW
on variable: sum_of_weights
Dependence polyhedron
Set #1
[2 dims; 5 constraints]
i >= 0
-i+7 >= 0
i' >= 0
-i'+7 >= 0
-i+i'-1 >= 0


T(S1): (0, i, 0)
loop types (loop, loop, loop)

[pluto] Number of statements: 1
[pluto] Total number of loops: 1
[pluto] Number of deps: 3
[pluto] Maximum domain dimensionality: 1
[pluto] Number of parameters: 0
[pluto] ddg_compute_scc
[pluto] dfs_for_scc: SCC 0: Stmt ids:  0


	SCC 0: size: 1: max stmt dim: 1
	No global context
[pluto] find_permutable_hyperplanes: max solution(s): 1; band depth: 0
[pluto] compute permutability constraints: Dep 1
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_p) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_o) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_n) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_m) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_l) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_k) from 3 constraints
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_q) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_p) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_o) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_n) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_m) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_l) from 4 constraints
	For dep: 1; num_constraints: 3
[pluto] compute permutability constraints: Dep 2
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_p) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_o) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_n) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_m) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_l) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_k) from 3 constraints
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_q) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_p) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_o) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_n) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_m) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_l) from 4 constraints
	For dep: 2; num_constraints: 3
[pluto] compute permutability constraints: Dep 3
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_p) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_o) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_n) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_m) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_l) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_k) from 3 constraints
[farkas_lemma_affine]
[farkas_lemma_affine] eliminating multiplier 0 (c_q) from 9 constraints
[farkas_lemma_affine] eliminating multiplier 1 (c_p) from 8 constraints
[farkas_lemma_affine] eliminating multiplier 2 (c_o) from 7 constraints
[farkas_lemma_affine] eliminating multiplier 3 (c_n) from 6 constraints
[farkas_lemma_affine] eliminating multiplier 4 (c_m) from 5 constraints
[farkas_lemma_affine] eliminating multiplier 5 (c_l) from 4 constraints
	For dep: 3; num_constraints: 3
	After dep: 1; num_constraints: 3
	After dep: 2; num_constraints: 6
	After dep: 3; num_constraints: 9
	After all dependences: num constraints: 3, num variables: 3
Adding lower bound 0 for transformation coefficients
Adding lower bound 0 for transformation coefficients
[pluto] get_linear_ind_constraints
[pluto] get_stmt_ortho constraints S1
Ortho constraints for S1; 1 disjuncts
Added ortho constraints for S1
linear independence constraints
[3 dims; 1 constraints]
      +c_j       -1 >= 0

[pluto] (Band 1) Solving for hyperplane #1
[pluto] pluto_prog_constraints_lexmin (3 variables, 8 constraints)
[pluto] pluto_constraints_lexmin_isl (3 variables, 8 constraints)
[pluto] find_permutable_hyperplanes: found a hyperplane
h(S1) = i
[pluto] pluto_auto_transform: band level 0; 1 hyperplane(s) found
T(S1): (i)
loop types (loop)

[pluto] dep_satisfaction_update (level 0)
[pluto] dep_satisfaction_update: dep 1 satisfied
[pluto] dep_satisfaction_update: dep 2 satisfied
[pluto] dep_satisfaction_update: dep 3 satisfied
	 3 dep(s) satisfied
[pluto] updating DDG
[pluto] pluto_auto_transform: successful, done
[pluto] pluto_detect_transformation_properties
[pluto] pluto_compute_dep_satisfaction
[pluto] pluto_dep_satisfaction_reset
[pluto] dep_satisfaction_update (level 0)
[pluto] dep_satisfaction_update: dep 1 satisfied
[pluto] dep_satisfaction_update: dep 2 satisfied
[pluto] dep_satisfaction_update: dep 3 satisfied
	 3 dep(s) satisfied
[pluto] Affine transformations [<iter coeff's> <param> <const>]

T(S1): (i)
loop types (loop)

t1 --> serial   loop   (band 0)no-ujam

[pluto] generating Cloog file...
[pluto] using Cloog -f/-l options: 1 1
[pluto] cloog_input_read
[pluto] cloog_clast_create
[pluto_mark_vector] parallel loops
[Pluto] Output written to fuseki.c_choose_corner_move_line174_loop.pluto.c
