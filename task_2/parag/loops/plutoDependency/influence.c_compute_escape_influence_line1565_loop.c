[pluto] compute_deps (isl)
nvar = 1, npar = 0
Parameters: 
S1 "active_caches[k] = 0;"
ndims: 1; orig_depth: 1
Index set
Set #1
[1 dims; 2 constraints]
k >= 0
-k+1 >= 0

T(S1): (0, k, 0)
loop types (loop, loop, loop)

No Read accesses
Write accesses
active_caches[k]
Original loop: 0 -> yes

** No dependences **

T(S1): (0, k, 0)
loop types (loop, loop, loop)

[pluto] Number of statements: 1
[pluto] Total number of loops: 1
[pluto] Number of deps: 0
[pluto] Maximum domain dimensionality: 1
[pluto] Number of parameters: 0
[pluto] ddg_compute_scc
[pluto] dfs_for_scc: SCC 0: Stmt ids:  0


	SCC 0: size: 1: max stmt dim: 1
	No global context
[pluto] find_permutable_hyperplanes: max solution(s): 1; band depth: 0
	After all dependences: num constraints: 0, num variables: 3
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
[pluto] pluto_prog_constraints_lexmin (3 variables, 5 constraints)
[pluto] pluto_constraints_lexmin_isl (3 variables, 5 constraints)
[pluto] find_permutable_hyperplanes: found a hyperplane
h(S1) = k
[pluto] pluto_auto_transform: band level 0; 1 hyperplane(s) found
T(S1): (k)
loop types (loop)

[pluto] dep_satisfaction_update (level 0)
	 0 dep(s) satisfied
[pluto] updating DDG
[pluto] pluto_auto_transform: successful, done
[pluto] pluto_detect_transformation_properties
[pluto] pluto_compute_dep_satisfaction
[pluto] pluto_dep_satisfaction_reset
[pluto] dep_satisfaction_update (level 0)
	 0 dep(s) satisfied
[pluto] Affine transformations [<iter coeff's> <param> <const>]

T(S1): (k)
loop types (loop)

t1 --> parallel loop   (band 0)no-ujam

[pluto] generating Cloog file...
[pluto] using Cloog -f/-l options: 1 1
[pluto] cloog_input_read
[pluto] cloog_clast_create
[pluto_mark_vector] parallel loops
t1 {loop with stmts: S1, }
[pluto_mark_vector] marking loop vectorizable
t1 {loop with stmts: S1, }
[Pluto] Output written to influence.c_compute_escape_influence_line1565_loop.pluto.c
