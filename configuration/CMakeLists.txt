# --------------------------------------------------------------------------------
#  CMake file for declaring and exporting procedurally generated configuration of the project
#
#  Zero Day Code, 2023 - Present
# --------------------------------------------------------------------------------

configure_file(
    "rlp_config.hpp.in"
    ${RLP_SOURCES_ROOT}/config/rlp_config.hpp ESCAPE_QUOTES
)
