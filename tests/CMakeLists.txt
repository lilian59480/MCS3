
add_executable(SrcProtocoleProtocole src_protocole_protocole.c)
target_link_libraries(SrcProtocoleProtocole Protocole Reseau ${CURSES_LIBRARIES} ${CDK_LIBRARIES})
add_test (NAME SrcProtocoleProtocole COMMAND SrcProtocoleProtocole)

add_executable(SrcProtocoleReponsesReponses src_protocole_reponses_reponses.c)
target_link_libraries(SrcProtocoleReponsesReponses Protocole Reseau ${CURSES_LIBRARIES} ${CDK_LIBRARIES})
add_test (NAME SrcProtocoleReponsesReponses COMMAND SrcProtocoleReponsesReponses)

add_executable(SrcProtocoleRequetesRequetes src_protocole_requetes_requetes.c)
target_link_libraries(SrcProtocoleRequetesRequetes Protocole Reseau ${CURSES_LIBRARIES} ${CDK_LIBRARIES})
add_test (NAME SrcProtocoleRequetesRequetes COMMAND SrcProtocoleRequetesRequetes)

