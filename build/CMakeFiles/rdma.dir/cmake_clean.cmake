file(REMOVE_RECURSE
  "librdma.a"
  "librdma.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/rdma.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
