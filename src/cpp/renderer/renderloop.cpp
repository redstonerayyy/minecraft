	// RENDER OPTIONS
	// Wireframes
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//avoid random drawing and not continous geometry
	glEnable(GL_DEPTH_TEST);
	//MSAA
	glEnable(GL_MULTISAMPLE);

	// RENDER LOOP
	while (!glfwWindowShouldClose(&window)){
		glfwSwapBuffers(&window);
		glfwPollEvents();
	}
	glfwTerminate();