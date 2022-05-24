PROJ_ROOT = $(abspath $(lastword $(MAKEFILE_LIST))/../)

JOBS=$(shell cat /proc/cpuinfo | grep "processor" | wc -l)
DOCS?=ON
PARDISO?=OFF
SUITESPARSE?=ON
NANOFLANN?=ON
JSON?=ON
GUI?=ON
COVERAGE?=OFF
REST_CONFIG?=
CLANG_FORMAT?=ON
CLANG_TIDY?=ON

.DEFAULT_GOAL := pipeline

_CMAKE_COMMON_CONFIG = \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
		-DCHAOS_BUILD_WITH_GUI=$(GUI) \
		-DCHAOS_BUILD_WITH_PARDISO=$(PARDISO) \
		-DCHAOS_BUILD_WITH_SUITESPARSE=$(SUITESPARSE) \
		-DCHAOS_BUILD_WITH_NANOFLANN=$(NANOFLANN) \
		-DCHAOS_BUILD_WITH_JSON=$(JSON) \
		-DCHAOS_USE_CLANGTIDY=$(CLANG_TIDY) \
		-DCHAOS_USE_CLANGFORMAT=$(CLANG_FORMAT) \
		-DCHAOS_BUILD_DOCS=$(DOCS) \
		$(if $(REST_CONFIG), $(REST_CONFIG),)

.PHONY: test release debug init \
	config-release config-debug \
	json-debug json-release \
	clean clean-debug clean-release prune

init:
	git submodule update --init --recursive

config-debug:
	cmake -S${PROJ_ROOT} -B${PROJ_ROOT}/build-debug \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCHAOS_BUILD_COVERAGE=$(COVERAGE) \
		$(_CMAKE_COMMON_CONFIG)

config-release:
	cmake -S${PROJ_ROOT} -B${PROJ_ROOT}/build-release \
		-DCMAKE_BUILD_TYPE=Release \
		$(_CMAKE_COMMON_CONFIG)

debug: config-debug
	cmake --build ${PROJ_ROOT}/build-debug -j$(JOBS)

release: config-release
	cmake --build ${PROJ_ROOT}/build-release -j$(JOBS)

json-debug: config-debug
	ln -sf ${PROJ_ROOT}/build-debug/compile_commands.json ${PROJ_ROOT}

json-release: config-release
	ln -sf ${PROJ_ROOT}/build-release/compile_commands.json ${PROJ_ROOT}

test: debug
	cmake --build ${PROJ_ROOT}/build-debug -t test -j ${JOBS}

format: debug
ifeq ($(CLANG_FORMAT), ON)
	cmake --build ${PROJ_ROOT}/build-debug -t code-format
endif

pipeline: test format

# legacy: subtree mode. currently use submodule mode.
# CMAKE_GIT_URL=git@github.com:LamKamhang/cmake.git
# add-cmake:
#	git subtree add --prefix=cmake $(CMAKE_GIT_URL) main --squash

# pull-cmake:
#	git subtree pull --prefix=cmake $(CMAKE_GIT_URL) main --squash

# push-cmake:
#	git subtree push --prefix=cmake $(CMAKE_GIT_URL) main

clean: clean-debug clean-release

clean-release:
	rm -rf build-release

clean-debug:
	rm -rf build-debug

prune:
	git remote prune origin

docker-build:
	docker build --network=host -t chaos:dev ${PROJ_ROOT}

docker-rebuild:
	docker build --no-cache --network=host -t chaos:dev ${PROJ_ROOT}

docker-run:
	docker run -it --rm \
		--network=host \
		--name chaos_dev chaos:dev
