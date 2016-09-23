void provideBodyRelationsTo(BodyRelation** arr) {
    // Cleaning array
    for(int i = 0; i < NUM_RELATIONS; i++) {
        arr[i] = NULL;
    }

    arr[0] = new BodyRelation("ElbowRight", 10, LEFT, 0, 2, 0);
    arr[1] = new BodyRelation("WristRight", 13, LEFT, 0, 1, 0);
}