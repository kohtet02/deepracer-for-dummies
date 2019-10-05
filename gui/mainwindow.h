#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtDebug>
#include <QProcess>
#include <QFileDialog>
#include <QVector>
#include <QtWebKitWidgets/QWebView>
#include <QUrl>
#include <QTimer>
#include <QCloseEvent>
#include <QtXml>
#include <QInputDialog>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void parse_logfile();

    void refresh();

    void update_log_analysis_browser();

    void on_start_button_clicked();

    void on_save_button_clicked();

    void on_restart_button_clicked();

    void on_stop_button_clicked();

    void on_init_button_clicked();

    void on_uploadbutton_clicked();

    void on_delete_button_clicked();

    void on_refresh_button_clicked();

    void go_to_notebook();

    void on_use_pretrained_button_clicked();

    void on_reward_function_textChanged();

    void on_action_space_textChanged();

    void on_track_name_textChanged();

    void on_hyper_parameters_textChanged();

    void on_actionSave_as_Profile_triggered();

    void on_actionLoad_Profile_triggered();

    void stop_training();

    void timer_stop();

private:
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent *event); //Do whatever needs to be done before window closes

    bool cpDir(const QString &srcPath, const QString &dstPath);

    //File paths for all the files that will be manipulated
    QString reward_func_path =  "../docker/volumes/minio/bucket/custom_files/reward.py";
    QString action_space_path =  "../docker/volumes/minio/bucket/custom_files/model_metadata.json";
    QString hyperparameters_path =  "../rl_deepracer_coach_robomaker.py";
    QString track_path = "../docker/.env";

    //Will be read in on application start
    QString current_reward_func = "";
    QString current_action_space = "";
    QString current_hyperparameters = "";
    QString current_track = "";

    //List of all editable hyperparameters
    QStringList hyperparams{"batch_size","num_epochs","stack_size","lr","exploration_type","e_greedy_value","epsilon_steps",
                            "beta_entropy","discount_factor","loss_type","num_episodes_between_training","term_cond_max_episodes",
                            "term_cond_avg_score"};
    //Script Paths and process definintions
    QString init_script =  qApp->applicationDirPath() + "/../init.sh";
    QProcess* init_process{nullptr};
    QString start_script =  qApp->applicationDirPath() + "/../scripts/training/start.sh";
    QProcess* start_process{nullptr};
    QString memory_manager_script =  qApp->applicationDirPath() + "/../scripts/training/memory-manager.sh";
    QProcess* memory_manager_process{nullptr};
    QString stop_script =  qApp->applicationDirPath() + "/../scripts/training/stop.sh";
    QProcess* stop_process{nullptr};
    QString use_pretrained_script = qApp->applicationDirPath() + "/../scripts/training/set-last-run-to-pretrained.sh";
    QString pretrained_path = qApp->applicationDirPath() + "/../docker/volumes/minio/bucket/rl-deepracer-pretrained";
    QProcess* use_pretrained_process{nullptr};
    QString upload_script = qApp->applicationDirPath() + "/../scripts/training/upload.sh";
    QProcess* upload_process{nullptr};
    QString delete_script = qApp->applicationDirPath() + "/../scripts/training/delete-last-run.sh";
    QProcess* delete_process{nullptr};
    QString log_analysis_script = qApp->applicationDirPath() + "/../scripts/log-analysis/start.sh";
    QProcess* log_analysis_process{nullptr};

    //Log file path and graphing vars
    QString log_path = "";
    QStringList log_format{"iteration", "steps", "x", "y", "yaw", "steer","throttle", "action", "reward", "done",
                           "on_track", "progress","closest_waypoint", "track_len", "timestamp"};
    QVector<double> reward_per_iteration_vector{};

    //Log analysis URL
    QString log_analysis_url = "";

    //XML for handling current model
    QDomDocument profiles_xml;
    QString profiles_path = qApp->applicationDirPath() + "/../profiles/profiles.xml";


    //General status variables
    bool is_running = false;
    bool is_pretrained = false;
    bool is_saved = true; //Used for warning the user if they are using something that may required something that has not been saved
    bool use_pretrained = false;

    //Training Timer
    QTimer* training_timer{nullptr};
};

#endif // MAINWINDOW_H
