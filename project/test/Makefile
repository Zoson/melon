OBJ_FILE = $(BUILD_DIR)/linear_neuron.o $(BUILD_DIR)/log_neuron.o $(BUILD_DIR)/linear_neuron.o $(BUILD_DIR)/reader.o $(BUILD_DIR)/vec.o $(BUILD_DIR)/mat.o $(BUILD_DIR)/func.o $(BUILD_DIR)/layer.o $(BUILD_DIR)/stump_neuron.o $(BUILD_DIR)/softmax_neuron.o $(BUILD_DIR)/object.o
TEST_OBJ = $(BUILD_DIR)/test.o
TEST_EXEC = $(BIN_DIR)/test
$(TEST_EXEC):$(TEST_OBJ) $(OBJ_FILE) 
	$(CC) $^ -o $@ -lstdc++
$(TEST_OBJ):test.cpp
	$(CC) -c $^ -o $@ -I$(INCLUDE)
