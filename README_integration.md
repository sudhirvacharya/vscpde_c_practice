INTEGRATION & RELEASE CHECKLIST
================================
Role: FW Integration Engineer
================================

SPRINT & JIRA MANAGEMENT
[ ] Receive Jira ticket - status "To Be Integrated"
[ ] Check prerequisite / dependency tickets are cleared
[ ] SWPM updated with latest integration status
[ ] Sprint board updated - move ticket to correct column

BEFORE INTEGRATION
[ ] Confirm baseline freeze - release branch is stable
[ ] Confirm only reviewed, tested, compliant changes are included
[ ] Code review / PR approved before merge
[ ] Verify branching strategy followed (dev -> integration -> product)

INTEGRATION
[ ] Integrate feature branch into release/product branch
[ ] Perform rebase / merge - resolve conflicts cleanly
[ ] Ensure no partial or incompatible feature merges
[ ] Update Jira ticket status -> "Integrated"

BUILD
[ ] Build the software across all supported configurations
[ ] Confirm build is clean - no broken build
[ ] Archive build artifact (binary/hex) with version label
[ ] Run static analysis / lint check
[ ] Check coding standards and commit quality

TESTING
[ ] Perform smoke test
[ ] Perform sanity test
[ ] Regression test
[ ] Full test (as applicable)
[ ] Triage any integration failures - drive fix with feature owners
[ ] Document test scope (what was tested / not tested)

QUALITY GATES
[ ] Quality gate check passed
[ ] SOP1 compliance verified
[ ] SOP2 compliance verified
[ ] Product branch is green and releasable

CROSS-TEAM COORDINATION
[ ] Communicate integration risks / conflicts to feature teams early
[ ] Sync with validation / QA team on test readiness
[ ] Update release / program management on integration status
[ ] Act as single point of accountability - confirm all teams aligned

TAGGING & RELEASE SUPPORT
[ ] Create tag with correct naming convention (e.g. v1.2.3-RC1)
[ ] Push tag to remote - git push origin <tagname>
[ ] Draft release notes / changelog
[ ] Ensure traceability - all features and fixes documented for this release

HANDOVER TO VALIDATION
[ ] Send build to validation team
[ ] Release mail - binary location, known issues, test scope, Jira filter link

POST-VALIDATION CLOSURE
[ ] Root-cause any late-stage integration or merge issues
[ ] Close all Jira tickets -> "Done / Released"
[ ] Merge release branch back to main/trunk
[ ] Repository hygiene check - structure, consistency, risky areas flagged

SPRINT CLOSURE
[ ] Sprint review / demo completed
[ ] Sprint retrospective done
[ ] SWPM final update
