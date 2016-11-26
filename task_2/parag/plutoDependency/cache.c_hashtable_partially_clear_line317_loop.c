[pluto] compute_deps (isl)
nvar = 2, npar = 0
Parameters: 
S1 "statistics[k][l] = 0;"
ndims: 2; orig_depth: 2
Index set
Set #1
[2 dims; 4 constraints]
k >= 0
-k+6 >= 0
l >= 0
-l+19 >= 0

T(S1): (0, k, 0, l, 0)
loop types (loop, loop, loop, loop, loop)

No Read accesses
Write accesses
statistics[k][l]
Original loop: 0 -> yes
Original loop: 1 -> yes

** No dependences **

T(S1): (0, k, 0, l, 0)
loop types (loop, loop, loop, loop, loop)

[pluto] Number of statements: 1
[pluto] Total number of loops: 2
[pluto] Number of deps: 0
[pluto] Maximum domain dimensionality: 2
[pluto] Number of parameters: 0
[pluto] ddg_compute_scc
[pluto] dfs_for_scc: SCC 0: Stmt ids:  0


	SCC 0: size: 1: max stmt dim: 2
	No global context
[pluto] find_permutable_hyperplanes: max solution(s): 2; band depth: 0
	After all dependences: num constraints: 0, num variables: 4
Adding lower bound 0 for transformation coefficients
Adding lower bound 0 for transformation coefficients
Adding lower bound 0 for transformation coefficients
Adding upper bound 18 for transformation coefficients
Adding upper bound 18 for transformation coefficients
Adding upper bound 18 for transformation coefficients
[pluto] get_linear_ind_constraints
[pluto] get_stmt_ortho constraints S1
Ortho constraints for S1; 2 disjuncts
Added ortho constraints for S1
linear independence constraints
[4 dims; 1 constraints]
      +c_j +c_k       -1 >= 0

[pluto] (Band 1) Solving for hyperplane #1
[pluto] pluto_prog_constraints_lexmin (4 variables, 9 constraints)
[pluto] pluto_constraints_lexmin_isl (4 variables, 9 constraints)
[pluto] find_permutable_hyperplanes: found a hyperplane
h(S1) = k
[pluto] get_linear_ind_constraints
[pluto] get_stmt_ortho constraints S1
Ortho constraints for S1; 1 disjuncts
Added ortho constraints for S1
linear independence constraints
[4 dims; 1 constraints]
            +c_k       -1 >= 0

[pluto] (Band 1) Solving for hyperplane #2
[pluto] pluto_prog_constraints_lexmin (4 variables, 9 constraints)
[pluto] pluto_constraints_lexmin_isl (4 variables, 9 constraints)
[pluto] find_permutable_hyperplanes: found a hyperplane
h(S1) = l
[pluto] pluto_auto_transform: band level 0; 2 hyperplane(s) found
T(S1): (k, l)
loop types (loop, loop)

[pluto] dep_satisfaction_update (level 0)
	 0 dep(s) satisfied
[pluto] updating DDG
[pluto] dep_satisfaction_update (level 1)
	 0 dep(s) satisfied
[pluto] updating DDG
[pluto] pluto_auto_transform: successful, done
[pluto] pluto_detect_transformation_properties
[pluto] pluto_compute_dep_satisfaction
[pluto] pluto_dep_satisfaction_reset
[pluto] dep_satisfaction_update (level 0)
	 0 dep(s) satisfied
[pluto] dep_satisfaction_update (level 1)
	 0 dep(s) satisfied
[pluto] Affine transformations [<iter coeff's> <param> <const>]

T(S1): (k, l)
loop types (loop, loop)

t1 --> parallel loop   (band 0)no-ujam
t2 --> parallel loop   (band 0)no-ujam

[pluto-intra-tile-opt] Score for loop 0: 10
t2 {loop with stmts: S1, }
[pluto-intra-tile-opt] Score for loop 1: -16
t1 {loop with stmts: S1, }
[pluto] generating Cloog file...
[pluto] using Cloog -f/-l options: 1 2
[pluto] cloog_input_read
[pluto] cloog_clast_create
[pluto_mark_vector] parallel loops
t2 {loop with stmts: S1, }
t1 {loop with stmts: S1, }
[pluto_mark_vector] marking loop vectorizable
t2 {loop with stmts: S1, }
[Pluto] Output written to cache.c_hashtable_partially_clear_line317_loop.pluto.c
