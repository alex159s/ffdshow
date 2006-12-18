[Messages]
WelcomeLabel1=[name/ver]

; English
en.WelcomeLabel2=This will install [name] on your computer.%n%nIt is recommended that you close all other applications before continuing.
en.FileAbortRetryIgnore=Quit the application using ffdshow and click Retry. If the problem persists, click Abort, restart your computer and setup again.
en.FinishedRestartLabel=To complete the installation of [name], Setup must restart your computer. Would you like to restart now?%n%nHint: To avoid restarting computer from the next time, it may be effective to enable "Info & debug"-"Don't use ffdshow in:"-"explorer.exe" in video decoder configuration.

#if localize
; Japanese
jp.WelcomeLabel2=このプログラムはご使用のコンピュータへ [name] をインストールします。%n%n続行する前に他のアプリケーションをすべて終了してください。
jp.FileAbortRetryIgnore=ffdshowを使用中のアプリケーションを終了して「再試行」をクリックしてください。解決しない場合は「中止」をクリックしてコンピュータを再起動後、もう一度セットアップを実行してください。
jp.FinishedRestartLabel=[name] のインストールを完了するためには、コンピュータを再起動する必要があります。%n%nすぐに再起動しますか？%n%nヒント：ビデオデコーダー設定の「情報とデバッグ」の「Don't use ffdshow in:」「explorer.exe」を有効にしておくと次回から再起動が不要になるかもしれません。
; German
de.WelcomeLabel2=Dieser Assistent wird jetzt [name] auf Ihrem Computer installieren.%n%nSie sollten alle anderen Anwendungen beenden, bevor Sie mit dem Setup fortfahren.
de.FileAbortRetryIgnore=Beenden sie das Programm, dass ffdshow verwendet und klicken sie auf "Wiederholen". Sollte das Problem weiterhin bestehen, klicken sie auf "Abbrechen", starten sie ihren Computer neu und f�hren sie das Setup erneut aus.
de.FinishedRestartLabel=Um die Installation von [name] zu fertig zu stellen, muss das Setup ihren Computer neu starten. Soll jetzt neu gestartet werden?%n%nHinweis: Um ihren Computer beim n臘hsten Mal nicht neu starten zu m�ssen, kann es helfen, in der Videodekoder-Konfiguration unter "Info" "ffdshow nicht verwenden in:" zu aktivieren.
; French
fr.WelcomeLabel2=Ceci installera [name] sur votre ordinateur.%n%nIl est recommand・de fermer toutes les autres applications avant de continuer.
; Russian
ru.WelcomeLabel2=ﾏ��胙瑟�� ���瑙�粨� [name] �� ﾂ璧 �������褞.%n%nﾐ裲��褊蔘褪�� 鈞����� 糂� ����韃 ��齏�趺��� �褞裝 �褌, �瑕 ���蒡�跖��.
ru.FileAbortRetryIgnore=ﾇ瑕��鶯� 糂� ��齏�趺���, 頌����銛��韃 ffdshow, � �琥�頸� "ﾏ�糘��". ﾅ��� �頸�璋�� ��糘��頸��, �琥�頸� "ﾎ��珸", �褞裼璢��鉅�� ﾂ璧 �������褞 � �����碯鶯� 襌ｸ �珸.
ru.FinishedRestartLabel=ﾄ�� 鈞粢��褊�� ���瑙�粲� [name] ��裔�褪�� �褞裼璢��鉅�� �������褞. ﾏ��韈粢��� �褞裼璢��鉤� �裨�瑰?%n%nﾏ�蓴�珸��: 韈砒赳�� �褞裼璢��鉤� �������褞� � ��裝���韜 �珸 ��趺� ������ 粲���褊韃 "ﾈ�����璋��"-"Don't use ffdshow in:"-"explorer.exe" � ����鞳��璋韋 粨蒟�蒟��蒟��.
; Add other languages here
#endif

[CustomMessages]
; English
en.langid=1033
en.ffdshowds=ffdshow DirectShow filter
en.vfwinterface=VFW interface
en.makeavis=AviSynth scripts serving
en.appplugins=Application plugins:
en.resetsettings=Reset all ffdshow settings
en.videoformats=Decode the following video formats with ffdshow:
en.genericMpeg4=Generic MPEG-4
en.rawvideo=RAW Video
en.audioformats=Decode the following audio formats with ffdshow:
en.rawaudio=RAW Audio
en.defaultfilters=Enable the following filters by default:
en.volumenorm=Volume normalization
en.subtitles=Subtitles
en.tweaks=Tweaks
en.skipinloop=Always skip H.264 inloop deblocking
en.audioconfig=Audio decoder configuration
en.videoconfig=Video decoder configuration
en.vfwconfig=VFW configuration
en.uninstall=Uninstall ffdshow
en.runaudioconfig=Run audio decoder configuration
en.runvideoconfig=Run video decoder configuration
en.runvfwconfig=Run VFW configuration
en.SelectPluginDirLabel1=Select %1 plugin Directory
en.SelectPluginDirLabel2=Where should %1 plugin be installed?
en.SelectPluginDirLabel3=Select the folder in which Setup should install %1 plugin, then click Next.

en.speakersetup=Speaker setup
en.SpeakerSetupLabel2=Select the speaker setup below that is most like the configuration on your computer. You can change it using "Mixer" settings after installation.
en.SpeakerSetupLabel3=Speaker setup:
en.spk_headphone=Head phone
en.spk_stereo=stereo
en.spk_quadro=quadro
en.spk_5ch=front 3ch + rear 2ch
en.spk_MixerDisable=disable Mixer
en.spk_front_3ch=front 3ch
en.spk_front_2ch=front 2ch
en.spk_Surround=surround
en.spk_Subwoofer=subwoofer
en.spk_mono=mono
en.spk_dolby1=Dolby Surround/ProLogic
en.spk_dolby2=Dolby ProLogic II
en.spk_sameasinput=same as input
en.spk_HRTF=Head-related transfer function(HRTF)

#if localize
; Japanese
jp.langid=1041
jp.ffdshowds=ffdshow DirectShow フィルター
jp.vfwinterface=VFW インターフェース
jp.makeavis=AviSynth スクリプトサービング
jp.appplugins=アプリケーションプラグイン
jp.resetsettings=ffdshowのすべての設定を初期値に戻す
jp.videoformats=以下のすべてのビデオフォーマットをffdshowでデコードする
jp.audioformats=以下のすべてのオーディオフォーマットをffdshowでデコードする
jp.defaultfilters=以下のフィルターを有効にする
jp.volumenorm=ボリューム ノーマライズ
jp.subtitles=字幕
jp.speakersetup=スピーカーの設定
jp.runaudioconfig=オーディオデコーダーの設定を行う
jp.runvideoconfig=ビデオデコーダーの設定を行う
jp.runvfwconfig=VFWの設定を行う
jp.audioconfig=オーディオデコーダーの設定
jp.videoconfig=ビデオデコーダーの設定
jp.vfwconfig=VFWの設定
jp.uninstall=ffdshowのアンインストール
jp.SelectPluginDirLabel1=%1 プラグインインストール先の指定
jp.SelectPluginDirLabel2=%1のインストール先を指定してください。
jp.SelectPluginDirLabel3=%1 プラグインをインストールするフォルダを指定して、「次へ」をクリックしてください。
jp.speakersetup=スピーカーの設定
jp.SpeakerSetupLabel2=現在のコンピュータ構成に最も近いスピーカーの種類を選んでください。%nインストール後に「ミキサーの設定」から変更することも出来ます。
jp.SpeakerSetupLabel3=スピーカーの種類

jp.spk_headphone=ヘッドフォン
jp.spk_stereo=ステレオ
jp.spk_quadro=フロント 2ch ＋ リア 2ch
jp.spk_5ch=フロント 3ch ＋ リア 2ch
jp.spk_MixerDisable=ミキサーを無効にする
jp.spk_Surround=サラウンド
jp.spk_Subwoofer=サブウーファー
jp.spk_front_2ch=フロント 2ch
jp.spk_front_3ch=フロント 3ch
jp.spk_mono=モノラル
jp.spk_dolby1=ドルビーサラウンド/プロロジック
jp.spk_dolby2=ドルビープロロジックII
jp.spk_sameasinput=入力と同じ
jp.spk_HRTF=頭部伝達関数 (HRTF)

; German
de.langid=1031
de.ffdshowds=ffdshow-DirectShow-Filter
de.vfwinterface=VFW-Interface
de.makeavis=Hilfe f�r AviSynth-Skripte
de.appplugins=Anwendungsplungins:
de.resetsettings=Alle ffdshow-Einstellungen zur�cksetzen
de.videoformats=Folgende Videoformate mit ffdshow dekodieren:
de.genericMpeg4=Gew�hnliches MPEG-4
de.rawvideo=Unkomprimierte Videodaten
de.audioformats=Folgende Audioformate mit ffdshow dekodieren:
de.rawaudio=Unkomprimierte Audiodaten
de.defaultfilters=Folgende Filter standardm葹ig aktivieren:
de.volumenorm=Lautst舐ke-Normalisierung
de.subtitles=Untertitel
de.tweaks=Optimierungen
de.skipinloop=Internes H.264-Deblocking immer �berspringen
de.audioconfig=Audiodekoder-Konfiguration
de.videoconfig=Videodekoder-Konfiguration
de.vfwconfig=VFW-Konfiguration
de.uninstall=ffdshow deinstallieren
de.runaudioconfig=Audiodekoder-Konfiguration ausf�hren
de.runvideoconfig=Videodekoder-Konfiguration ausf�hren
de.runvfwconfig=VFW-Konfiguration ausf�hren
de.SelectPluginDirLabel1=%1pluginordner ausw臧len
de.SelectPluginDirLabel2=Wohin soll das %1plugin installiert werden?
de.SelectPluginDirLabel3=Bitte w臧len Sie den Ordner, in den das %1plugin insalliert werden soll. Klicken sie anschlieﾟend auf "Weiter".

de.speakersetup=Lautsprechteraufbau
de.SpeakerSetupLabel2=W臧len sie unten den Lautsprecheraufbau, der am ehesten Ihrer Konfiguration entspricht. Diese Einstellung kann nach der Installation unter "Mixer" ge舅dert werden.
de.SpeakerSetupLabel3=Lautsprechteraufbau:
de.spk_headphone=Kopfh�hrer
de.spk_mono=Mono
de.spk_stereo=Stereo
de.spk_quadro=Quadro
de.spk_5ch=3 Vorderkan舁e + 2 R�ckkan舁e
de.spk_MixerDisable=Mixer deaktivieren
de.spk_front_3ch=3 Vorderkan舁e
de.spk_front_2ch=2 Vorderkan舁e
de.spk_Surround=Surround
de.spk_Subwoofer=Subwoofer
de.spk_dolby1=Dolby Surround/ProLogic
de.spk_dolby2=Dolby ProLogic II
de.spk_sameasinput=identisch mit Eingangskan舁en
de.spk_HRTF=Head-related transfer function(HRTF)

; French
fr.langid=1036
fr.ffdshowds=Filtre ffdshow DirectShow
fr.vfwinterface=Interface VFW
fr.makeavis=Service de scripts AviSynth
fr.appplugins=Plugins d'applications :
fr.resetsettings=R駟nitialiser tous les param鑼res ffdshow
fr.videoformats=D馗oder les formats vid駮 suivants avec ffdshow :
fr.audioformats=D馗oder les formats audio suivants avec ffdshow :
fr.defaultfilters=Activer les filtres suivant par d馭aut :
fr.volumenorm=Normalisation du volume
fr.subtitles=Sous-titres
fr.speakersetup=Configuration des haut-parleurs :
fr.tweaks=Optimisations
fr.skipinloop=Toujours sauter le deblocking int馮r・H.264
fr.audioconfig=Configuration d馗odeur audio
fr.videoconfig=Configuration d馗odeur vid駮
fr.vfwconfig=Configuration VFW
fr.uninstall=D駸installer ffdshow
fr.runaudioconfig=Lancer la configuration d馗odeur audio
fr.runvideoconfig=Lancer la configuration d馗odeur vid駮
fr.runvfwconfig=Lancer la configuration VFW

; Russian
ru.langid=1049
ru.ffdshowds=ffdshow DirectShow-�齏���
ru.vfwinterface=VFW 竟�褞�裨�
ru.makeavis=ﾎ碵��跖籵�韃 ���韵��� AviSynth
ru.appplugins=ﾏ�璢竟� ��齏�趺�韜:
ru.resetsettings=ﾑ碣��頸� 糂� �瑰���鳰� ffdshow
ru.videoformats=ﾄ裲�蒻��籵�� ��裝���韃 粨蒟�����瑣� � ffdshow:
ru.genericMpeg4=Generic MPEG-4
ru.rawvideo=RAW Video
ru.audioformats=ﾄ裲�蒻��籵�� ��裝���韃 瑪蒻�����瑣� � ffdshow:
ru.rawaudio=RAW Audio
ru.defaultfilters=ﾂ����頸� ��裝���韃 �齏���� �� �����瑙��:
ru.volumenorm=ﾍ���琿韈璋�� 鈔���
ru.subtitles=ﾑ�碪頸��
ru.tweaks=ﾎ��韲韈璋韋
ru.skipinloop=ﾎ�����頸� ��碵�粢���� 蒟硴��竟� H.264
ru.audioconfig=ﾊ���鞳��璋�� 瑪蒻�蒟��蒟��
ru.videoconfig=ﾊ���鞳��璋�� 粨蒟�蒟��蒟��
ru.vfwconfig=ﾊ���鞳��璋�� VFW 竟�褞�裨��
ru.uninstall=ﾄ裴���琿����� ffdshow
ru.runaudioconfig=ﾇ瑜���頸� ����鞳��璋�� 瑪蒻�蒟��蒟��
ru.runvideoconfig=ﾇ瑜���頸� ����鞳��璋�� 粨蒟�蒟��蒟��
ru.runvfwconfig=ﾇ瑜���頸� ����鞳��璋�� VFW 竟�褞�裨��
ru.SelectPluginDirLabel1=ﾂ�碚� �瑜�� ��璢竟� 蓁� %1
ru.SelectPluginDirLabel2=ﾂ �瑕�� �瑜�� 蒡�趺� 磊�� ���瑙�粱褊 ��璢竟 蓁� %1?
ru.SelectPluginDirLabel3=ﾂ�砒�頸� �瑜��, � ������� 蒡�趺� 磊�� ���瑙�粱褊 ��璢竟 蓁� %1, 鈞�褌 �琥�頸� "ﾄ琿裹".

ru.speakersetup=ﾍ瑰���鳰� 瑪蒻��頌�褌�
ru.SpeakerSetupLabel2=ﾂ�砒�頸� ����鞳��璋�� 蒻�瑟韭��, ��糀琅����� � ﾂ璧裨. ﾂ� ��趺�� 韈�褊頸� 蟶 ����� ���瑙�粲�, 頌����銛� �瑰���鳰� "ﾌ韭�褞".
ru.SpeakerSetupLabel3=ﾀ�蒻��頌�褌�:
ru.spk_headphone=�瑪��韭�
ru.spk_stereo=��褞褓
ru.spk_quadro=�籵蓿�
ru.spk_5ch=5 �瑙琿��
ru.spk_MixerDisable=������頸� ﾌ韭�褞
ru.spk_front_3ch=3 �褞裝�頷 �瑙琿�
ru.spk_front_2ch=2 �褞裝�頷 �瑙琿�
ru.spk_Surround=�磅ｸ����
ru.spk_Subwoofer=�珮糒�褞
ru.spk_mono=����
ru.spk_dolby1=Dolby Surround/ProLogic
ru.spk_dolby2=Dolby ProLogic II
ru.spk_sameasinput=��糀琅瑯� �� 糢�蒡�
ru.spk_HRTF=Head-related transfer function (HRTF)

; Add other languages here
ba.langid=1069
br.langid=1046
ca.langid=1027
cz.langid=1029
da.langid=1030
du.langid=1043
fi.langid=1035
hu.langid=1038
it.langid=1040
no.langid=1044
pl.langid=1045
pr.langid=2070
sk.langid=1051
sn.langid=1060
sp.langid=3082
#endif
