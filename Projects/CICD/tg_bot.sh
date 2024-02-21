#!/bin/bash
TELEGRAM_BOT_TOKEN="6975526878:AAHsPF0P6B_F99LBe34SnY33OMyVE5DSMYY"
TELEGRAM_USER_ID="680960962"
TIME="10"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $1+$2%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG%0ACommited by:+$CI_COMMIT_AUTHOR%0A"
curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
