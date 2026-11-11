idf_component_register(
    SRCS "main.c" "control_logic.c" "ind236_driver.c"
    INCLUDE_DIRS "."
    REQUIRES driver esp_timer nvs_flash
)
