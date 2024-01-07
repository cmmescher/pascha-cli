set(HEADER_LIST
  ${PROJECT_SOURCE_DIR}/include/pascha/calculation_method_decorator.h
  ${PROJECT_SOURCE_DIR}/include/pascha/calculation_methods.h
  ${PROJECT_SOURCE_DIR}/include/pascha/calculation_options.h
  ${PROJECT_SOURCE_DIR}/include/pascha/calendar_conversion.h
  ${PROJECT_SOURCE_DIR}/include/pascha/date.h
  ${PROJECT_SOURCE_DIR}/include/pascha/i_calculation_method.h
  ${PROJECT_SOURCE_DIR}/include/pascha/i_calculator_model.h
  ${PROJECT_SOURCE_DIR}/include/pascha/i_controller.h
  ${PROJECT_SOURCE_DIR}/include/pascha/i_observable.h
  ${PROJECT_SOURCE_DIR}/include/pascha/i_observer.h
  ${PROJECT_SOURCE_DIR}/include/pascha/i_view.h
  ${PROJECT_SOURCE_DIR}/include/pascha/output_calendar.h
  ${PROJECT_SOURCE_DIR}/include/pascha/output_calendars.h
  ${PROJECT_SOURCE_DIR}/include/pascha/output_option.h
  ${PROJECT_SOURCE_DIR}/include/pascha/output_options.h
  ${PROJECT_SOURCE_DIR}/include/pascha/pascha_calculator_model.h
  ${PROJECT_SOURCE_DIR}/include/pascha/target_date.h
  ${PROJECT_SOURCE_DIR}/include/pascha/target_dates.h
  ${PROJECT_SOURCE_DIR}/include/pascha/typedefs.h
)

add_library(
  pascha-lib
  calculation_method_decorator.cpp
  calculation_methods.cpp
  calendar_conversion.cpp
  output_calendars.cpp
  output_options.cpp
  pascha_calculator_model.cpp
  target_date.cpp
  ${HEADER_LIST}
)

target_include_directories(pascha-lib PUBLIC ../include)

target_compile_features(pascha-lib PUBLIC cxx_std_20)

# IDE header organization
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
